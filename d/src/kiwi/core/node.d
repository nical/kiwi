module kiwi.core.node;

import kiwi.core.commons;
import kiwi.core.data;
import kiwi.core.port;
import kiwi.core.nodetree;



class Node
{
    this( string nodeName
        , InputDescriptor[] inputDesc, OutputDescriptor[] outputDesc
        , NodeUpdater updater = null)
    {
        _name = nodeName;

        foreach( desc ; inputDesc )
            _inputs ~= new InputPort( desc.name, this, desc.compatibility
            , desc.accessFlags, desc.isOptional );

        foreach( desc ; outputDesc )
            _outputs ~= new OutputPort( desc.name, this, desc.data );    

        _updater = updater;
    }
    

    @property string name() { return _name; }
    
    InputPort input(uint index = 0)
    {
        return _inputs[index];
    }

    OutputPort output(uint index = 0)
    {
        return _outputs[index];
    }

    @property
    {

        InputPort[] inputs()
        {
            return _inputs;
        }

        OutputPort[] outputs()
        {
            return _outputs;
        }

        uint inputCount() const
        {
            return _inputs.length;
        }

        uint outputCount() const
        {
            return _outputs.length;
        }
        
        NodeTree nodeTree()
        {
            return _nodeTree;
        }

        void update()
        {
            mixin( logFunction!"Node.update" );
            if(_updater !is null) _updater.update(this);
        }
    }//properties
    
private:
    InputPort[]     _inputs;
    OutputPort[]    _outputs;
    NodeTree        _nodeTree;
    NodeUpdater     _updater;
    string          _name;
}

interface NodeUpdater
{
    void update(Node n);
}


struct OutputDescriptor
{
    string name;
    DataStrategy data;
}


struct InputDescriptor
{
    string name;
    CompatibilityStrategy compatibility;
    DataAccessFlag accessFlags;
    bool isOptional;
}


class FunctionUpdate : NodeUpdater
{
    alias void function(Data[],Data[]) UpdateFunction;

    this(UpdateFunction func)
    {
        _update = func;
    }
    
    override void update(Node n)
    {
        mixin( logFunction!"FunctionUpdate.update" );
        Data[] inputs;
        Data[] outputs;
        foreach( input ; n.inputs )
        {
            if ( !input.isOptional && !input.isConnected )
                return;
            inputs ~= input.data;
        }
        foreach( output ; n.outputs )
            outputs ~= output.data;

        _update(inputs, outputs);
    }
    
    UpdateFunction _update;
}

version(unittest)
{
    int execCount = 0;

    void updateTestFunc(Data[],Data[])
    {
        mixin( logFunction!"updateTestFunc" );
        ++execCount;
    }
}

unittest
{
    mixin( logTest!"kiwi.core.core" );

    auto n = new Node( "dummy",[],[], new FunctionUpdate(&updateTestFunc) );

    assert( execCount == 0 );
    n.update;
    n.update;
    assert( execCount == 2 );
}
