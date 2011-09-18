module kiwi.core.node;

import kiwi.core.commons;
import kiwi.core.data;
import kiwi.core.port;
import kiwi.core.nodetree;



class Node
{
    this( string nodeName, InputDescriptor[] inputDesc, OutputDescriptor[] outputDesc  )
    {
        _name = nodeName;

        foreach( desc ; inputDesc )
            _inputs ~= new InputPort( desc.name, this, desc.compatibility
            , desc.accessFlags, desc.isOptional );

        foreach( desc ; outputDesc )
            _outputs ~= new OutputPort( desc.name, this, desc.data );    
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

    InputPort[] inputs()
    {
        return _inputs;
    }

    OutputPort[] outputs()
    {
        return _outputs;
    }

    NodeTree nodeTree()
    {
        return _nodeTree;
    }
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


class FunctionUpdate
{
    alias void function(Data[],Data[]) UpdateFunction;

    this(UpdateFunction func)
    {
        _update = func;
    }
    void update(Node)
    {
        
    }
    
    UpdateFunction _update;
}
