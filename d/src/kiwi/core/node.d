module kiwi.core.node;

import kiwi.core.commons;
import kiwi.core.port;
import kiwi.core.pipeline;
import kiwi.core.nodeinfo;
import kiwi.core.runtimetype;
import kiwi.utils.hstring;

struct Node
{
    /++
     + Nodes initialization occurs after constructions. This means a node's state
     + is invalid between the constructor and initialize stages.
     +/ 
    void initialize( Pipeline* p, const NodeTypeInfo* nodeInfo )
    {
        _pipeline = p;
        _nodeTypeInfo = nodeInfo;
        _inputs.length  = _nodeTypeInfo.inputs.length;
        _outputs.length = _nodeTypeInfo.outputs.length;
        for( ubyte i = 0; i < _inputs.length; ++i )
        {
            _inputs[i].initialize(&this, i);
        }
        for( ubyte i = 0; i < _outputs.length; ++i )
        {
            _outputs[i].initialize(&this, i);
        }
    }
    
    alias uint NodeTypeID;
    
    
    ref inout(InputPort) input( uint index = 0 ) inout pure
    {
        return _inputs[index];
    }

    ref inout(OutputPort) output( uint index = 0 ) inout pure
    {
        return _outputs[index];
    }

    ref InputPort input( StrHash pname ) pure
    {
        foreach( ref p ; _inputs )
            if ( p.name == pname )
                return p;

        throw new PortNameNotFoundException("Node.input(StrHash)", __FILE__, __LINE__);
    }

    ref OutputPort output( StrHash pname ) pure
    {
        foreach( ref p ; _outputs )
            if ( p.name == pname )
                return p;

        throw new PortNameNotFoundException("Node.output(StrHash)", __FILE__, __LINE__);
    }

    bool update()
    {
        bool status = true;

        if (info.onUpdate)
            status = info.onUpdate( &this );
        
        if (info.onProcess)
        {
            RuntimeType*[] inputData, outputData;
            /+
            foreach(i, ip ; _inputs ){
                inputData ~= &(ip.data());
                log.writeln(i,"## ", &ip," ",&(ip.data()));
                assert( &ip is &_inputs[i] ); // OMGWTFBBQ ??
            }+/
            for(int i = 0; i < _inputs.length; ++i)
                inputData ~= &(_inputs[i].data());
            for(int i = 0; i < _outputs.length; ++i)
                outputData ~= &(_outputs[i].data());
            //foreach( op ; _outputs )
            //    outputData ~= &(op.data());
            status &= info.onProcess( inputData, outputData );
        }
        return status;
    }
    
    void outputConnected(OutputPort* port, InputPort* to)
    {
        
    }

    @property 
    {
        const(NodeTypeInfo)* info() const  pure
        {
            return _nodeTypeInfo;
        }
        
        auto inputs() inout pure
        {
            return _inputs[0..$];
        }
        
        auto outputs() inout pure
        {
            return _outputs[0..$];
        }

        
        auto name() const pure
        {
            return _nodeTypeInfo.name;
        }
        
        auto previousNodes() inout pure
        {
            return _previousNodes[0..$];
        }
        
        auto nextNodes() inout pure
        {
            return _nextNodes[0..$];
        }
    }
    
private:
    InputPort[]    _inputs;
    OutputPort[]   _outputs;
    NodeTypeID     _nodeTypeId;
    Pipeline *     _pipeline;
    const(NodeTypeInfo)*  _nodeTypeInfo;
    // cached for efficiency, updated from port.d
    package Node*[] _previousNodes;
    package Node*[] _nextNodes;
 
}

class PortNameNotFoundException : Exception
{
    this(string msg, string file = null, uint line = 0)
    {
        super(msg ~ " is not implemented yet.", file, line);
    }
}


unittest
{
    import kiwi.utils.testing;
    import kiwi.utils.hstring;
    
    auto unit = TestSuite("kiwi.core.node");

    DataTypeID intID;

    auto nUpdate = delegate(Node*) {
        log.writeln("Node updating");
        return true;
    };
    
    NodeTypeInfo ntinfo = {
        name : StrHash("NodeName"),
        inputs : [
            { StrHash("in#1"), intID, READ },
            { StrHash("in#2"), intID, READ }
        ],
        outputs : [
            { StrHash("out"), intID, READ },
        ],
        onUpdate : nUpdate
    };

    Node n1;
    n1.initialize( null, &ntinfo );
    
    unit.test( &n1.inputs[0] is &n1._inputs[0], "Input port range random access" );
    unit.test( &n1.outputs[0] is &n1._outputs[0], "Output port range random access" );
    unit.test( n1.inputs.length == n1._inputs.length, "Input port range length" );
    unit.test( n1.outputs.length == n1._outputs.length, "Output port range length" );
    
    unit.test( n1.input(0) is n1.input(StrHash("in#1")), "Access input port by name" );
    unit.test( n1.input(1) is n1.input(StrHash("in#2")), "Access input port by name" );
    unit.test( n1.output(0) is n1.output(StrHash("out")), "Access output port by name" );

}
