module kiwi.core.node;

import kiwi.core.commons;
import kiwi.core.data;
import kiwi.core.port;
import kiwi.core.nodetree;

import std.exception;


/**
 * Represents an active element of the pipeline.
 *
 * Nodes are mainly used to execute algorithms. The input parameters and dependencies
 * are defined by the node's input ports, and the result can be collected through the
 * output ports.
 */ 
final class Node
{
    /**
     * Constructor.
     */ 
    this( NodeTypeInfo nodeTypeInfo
        , InputDescriptor[] inputDesc, OutputDescriptor[] outputDesc
        , NodeUpdater updater = null)
    {
        _typeInfo = nodeTypeInfo;
        
        foreach( desc ; inputDesc )
            _inputs ~= new InputPort( desc.name, this, desc.compatibility
                , desc.accessFlags, desc.isOptional );

        foreach( desc ; outputDesc )
            _outputs ~= new OutputPort( desc.name, this, desc.data );    

        _updater = updater;
    }

    /**
     * Returns an input by index.
     *
     * No range checking is performed.
     */     
    InputPort input(uint index = 0)
    {
        return _inputs[index];
    }

    /**
     * Returns an output by index.
     *
     * No range checking is performed.
     */ 
    OutputPort output(uint index = 0)
    {
        return _outputs[index];
    }

    /**
     * Gets an input port by name.
     *
     * If two inputs has the same name, the one with the lowest index is returned.
     * If no inputs has the name passed in parameter, a null reference is returned.
     */ 
    InputPort input(string portName)
    {
        foreach ( ip ; _inputs )
            if (ip.name == portName)
                return ip;
        return null;
    }

    /**
     * Gets an output port by name.
     *
     * If two outputs has the same name, the one with the lowest index is returned.
     * If no output has the name passed in parameter, a null reference is returned.
     */ 
    OutputPort output(string portName)
    {
        foreach ( op ; _outputs )
            if (op.name == portName)
                return op;
        return null;
    }

    @property
    {
        /**
         * Returns this node's name.
         */ 
        string name() const
        {
            if (_typeInfo !is null)
                return _typeInfo.name;
            return "";
        }

        /**
         * Returns this node's input ports in an array.
         */
        InputPort[] inputs()
        {
            return _inputs;
        }

        /**
         * Returns this node's output ports in an array.
         */
        OutputPort[] outputs()
        {
            return _outputs;
        }

        /**
         * Returns the number of input ports.
         */ 
        uint inputCount() const
        {
            return _inputs.length;
        }

        /**
         * Returns the number of output ports.
         */ 
        uint outputCount() const
        {
            return _outputs.length;
        }
        
        NodeTree nodeTree()
        {
            return _nodeTree;
        }

        /**
         * Return a reference to this node's runtime type information.
         */ 
        const(NodeTypeInfo) type() const
        {
            return _typeInfo;
        }

        /**
         * Invokes this node's updater if any.
         *
         * Should be called only if the inputs and outputs are properly connected.
         */ 
        void update()
        {
            mixin( logFunction!"Node.update" );
            if(_updater !is null) _updater.update(this);
        }

        /**
         * Returns the set of nodes connected to this node's inputs.
         */ 
        Node[] previousNodes()
        {
            Node[] result;
            foreach( ip ; _inputs )
            {
                if ( ip.node is null )
                    continue;
                bool found = false;
                foreach( res ; result )
                {
                    if( ip.node is res )
                    {
                        found = true;
                        break;
                    }
                }
                if ( !found )
                    result ~= ip.node;
            }
            return result;
        }

        /**
         * Returns the set of nodes connected to this node's outputs.
         */ 
        Node[] nextNodes()
        {
            Node[] result;
            foreach( op ; _outputs )
            {
                if ( op.node is null )
                    continue;
                bool found = false;
                foreach( res ; result )
                {
                    if( op.node is res )
                    {
                        found = true;
                        break;
                    }
                }
                if ( !found )
                    result ~= op.node;
            }
            return result;
        }
        
    }//properties
    
private:
    InputPort[]     _inputs;
    OutputPort[]    _outputs;
    NodeTree        _nodeTree;
    NodeUpdater     _updater;
    NodeTypeInfo    _typeInfo;
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
        null, // data.type.name ~ " container"
        [ ],
        [ DeclareOutput("data", new UserAllocatedDataStrategy(data, accessFlags)) ],
        null
    );
}








/**
 * Runtime Type information structure for nodes.
 *
 * Should be stored in the NodeTypeManager. 
 */ 
class NodeTypeInfo
{
    alias Node function() Instanciator;
    enum{ NOTAG, ALGORITHM, LOADER, CONTAINER }

    /**
     * Constructor.
     */ 
    this(string nodeName, string nodeCategory, int nodeTag
        , Instanciator newFunc, Object[string] components )
    {
        _name = nodeName;
        _category = nodeCategory;
        _tag = nodeTag;
        _newInstance = newFunc;
        _components = components;
    }

    @property
    {
        /**
         * Name of this type of node.
         *
         * For example: "Multiply"
         */ 
        string name() const
        {
            return _name;
        }

        /**
         * Category of this type of node.
         *
         * For example: "Text"
         */ 
        string category() const
        {
            return _category;
        }

        /**
         * A tag that gives some information on the nature of the node (is it an algorithm,
         * a data container...).
         */ 
        int tag() const
        {
            return _tag;
        }

        /**
         * Returns a new instance of this type of node.
         */ 
        Node newInstance() const
        {
            if (_newInstance !is null)
                return _newInstance();
            else return null;
        }
    }

    /**
     * Returns an optional component associated to the key if it exists.
     *
     * Optional components may be used to bring any kind of additional informations
     * uch as a description or some kind of semantic info...
     */ 
    Object component(string key)
    {
        if ( key in _components )
            return _components[key];
        return null;
    }

private:
    string _name;
    string _category;
    int _tag;
    Object[string] _components;
    Instanciator _newInstance;
}



class NodeTypeManager
{

    static NodeTypeInfo Register(
        string nodeName, string nodeCategory, int nodeTag
        , NodeTypeInfo.Instanciator newFunc, Object[string] components )
    {
        if ( Contains( nodeName ) )
            return Get(nodeName);

        auto temp = new NodeTypeInfo( nodeName, nodeCategory, nodeTag, newFunc, components );
        _nodeTypes[nodeName] = temp;
        return temp;        
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
        return ((key in _nodeTypes) !is null);
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
    mixin( logTest!"kiwi.core.node" );

    assert( !NodeTypeManager.Contains("NodeTypeTest") );
    NodeTypeManager.Register("NodeTypeTest","Test", NodeTypeInfo.NOTAG, null, null);
    assert( NodeTypeManager.Contains("NodeTypeTest") );
    assert( NodeTypeManager["NodeTypeTest"].name == "NodeTypeTest" );
    assert( NodeTypeManager["NodeTypeTest"].category == "Test" );
    assert( NodeTypeManager["NodeTypeTest"].tag == NodeTypeInfo.NOTAG );
    assert( NodeTypeManager["NodeTypeTest"] is NodeTypeManager["NodeTypeTest"] );

    auto n = new Node( null,[],[], new FunctionUpdate(&updateTestFunc) );

    assert( execCount == 0 );
    n.update;
    n.update;
    assert( execCount == 2 );

    
    auto n2 = new Node(
        NodeTypeManager["NodeTypeTest"],
        [ // inputs
            DeclareInput( "in1", new AlwaysCompatible, READ ),
            DeclareInput( "in2", new AlwaysCompatible, READ )
        ],
        [ // outputs
            DeclareOutput( "out", new UserAllocatedDataStrategy(cast(DataTypeInfo)null, READ) )
        ],
        new FunctionUpdate(&updateTestFunc)
    );
    assert( n2.name == "NodeTypeTest" );
    assert( n2.inputs.length == 2 );
    assert( n2.outputs.length == 1 );

    assert( !n2.input(0).isOptional );
    assert( !n2.input(1).isOptional );
    try{
        n2.update;
        assert(false, "Calling update on n2 should have thrown an exception as inputs are not optional");
    }catch(Exception e){ }
    assert( execCount == 2 );
    
}
