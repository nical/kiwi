module kiwi.core.node;

import kiwi.core.commons;
import kiwi.core.data;
import kiwi.core.port;
import kiwi.core.nodetree;

import std.exception;



final class Node
{
    this( string nodeName
        , NodeTypeInfo nodeTypeInfo
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
    
    InputPort input(uint index = 0)
    {
        return _inputs[index];
    }

    OutputPort output(uint index = 0)
    {
        return _outputs[index];
    }

    InputPort input(string portName)
    {
        foreach ( ip ; _inputs )
            if (ip.name == portName)
                return ip;
        return null;
    }

    OutputPort output(string portName)
    {
        foreach ( op ; _outputs )
            if (op.name == portName)
                return op;
        return null;
    }

    @property
    {
        string name()
        {
            return _name;
        }

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

        NodeTypeInfo type()
        {
            return _typeInfo;
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
    NodeTypeInfo    _typeInfo;
    string          _name;
}

interface NodeUpdater
{
    void update(Node n);
}


struct OutputDescriptor
{
    this( string portName, DataStrategy dataStrategy )
    {
        name = portName;
        data = dataStrategy;
    }
    string name;
    DataStrategy data;
}


struct InputDescriptor
{
    this( string name_, CompatibilityStrategy compatibility_, DataAccessFlag flags, bool opt = false)
    {
        name = name_;
        compatibility = compatibility_;
        accessFlags = flags;
        isOptional = opt;
    }
    string name;
    CompatibilityStrategy compatibility;
    DataAccessFlag accessFlags;
    bool isOptional;
}

alias InputDescriptor DeclareInput;
alias OutputDescriptor DeclareOutput;

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
            {
                throw new Exception("node.FunctionUpdate: Input port "~input.name~" of node "~n.name~" is not optional, yet it is not connected while update is invoked.");
                return;
            }
            inputs ~= input.data;
        }
        foreach( output ; n.outputs )
            outputs ~= output.data;

        _update(inputs, outputs);
    }
    
    UpdateFunction _update;
}

Node NewContainerNode( Data data, int accessFlags = 3 ) // 3=READ_WRITE
in{ assert( data !is null ); }
body
{
    return new Node
    (
        data.type.name ~ " container",
        null,
        [ ],
        [ DeclareOutput("data", new UserAllocatedDataStrategy(data, accessFlags)) ],
        null
    );
}









class NodeTypeInfo
{
    alias Node function() Instanciator;

    this(string nodeName, string nodeCategory, Instanciator newFunc, Object[string] components )
    {
        _name = nodeName;
        _category = nodeCategory;
        _newInstance = newFunc;
        _components = components;
    }

    @property
    {
        string name()
        {
            return _name;
        }

        string gategory()
        {
            return _category;
        }
        
        Node newInstance()
        {
            if (_newInstance !is null)
                return _newInstance();
            else return null;
        }
    }

    Object component(string key)
    {
        if ( key in _components )
            return _components[key];
        return null;
    }

private:
    string _name;
    string _category;
    Object[string] _components;
    Instanciator _newInstance;
}



class NodeTypeManager
{

    static NodeTypeInfo Register( _Type )()
    {
        NotImplemented("NodeTypeManager.Register");
    }

    static Node Create( string key )
    {
        auto info = Get( key );
        if ( info !is null )
        {
            return info.newInstance(); 
        }
        else 
        {
            // TODO: return an exception instead
            return null;
        }
    }

    static bool Contains( string key )
    {
        foreach( existing ; _nodeTypes.byKey )
          if ( existing == key )
            return true;
        return false;
    }

    static auto Keys()
    {
        return _nodeTypes.keys;
    }


    static NodeTypeInfo Get(string key)
    {
        return opIndex( key );
    }

    static NodeTypeInfo opIndex( string key )
    {
        if( Contains(key) ) 
            return _nodeTypes[key];
        else
            return null;
    }
    
private: 
    this(){ mixin( logFunction!"NodeTypeManager.constructor"); }
    static NodeTypeInfo[string] _nodeTypes;
}






//            #####   #####    ####   #####    ####
//              #     #       #         #     #
//              #     ###      ###      #      ###
//              #     #           #     #         #
//              #     #####   ####      #     ####



version(unittest)
{
    import kiwi.core.datastrategy;
    
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

    auto n = new Node( "nodeTest1",null,[],[], new FunctionUpdate(&updateTestFunc) );

    assert( execCount == 0 );
    n.update;
    n.update;
    assert( execCount == 2 );

    
    auto n2 = new Node(
        "nodeTest2",
        null,
        [ // inputs
            DeclareInput( "in1", new AlwaysCompatible, READ ),
            DeclareInput( "in2", new AlwaysCompatible, READ )
        ],
        [ // outputs
            DeclareOutput( "out", new UserAllocatedDataStrategy(cast(DataTypeInfo)null, READ) )
        ],
        new FunctionUpdate(&updateTestFunc)
    );
    assert( n2.name == "nodeTest2" );
    assert( n2.inputs.length == 2 );
    assert( n2.outputs.length == 1 );

    assert( !n2.input(0).isOptional );
    assert( !n2.input(1).isOptional );
    try{
        n2.update;
        assert(false, "Calling update on n2 should throw an exception as inputs are not optional");
    }catch(Exception e){ }
    assert( execCount == 2 );
    
}
