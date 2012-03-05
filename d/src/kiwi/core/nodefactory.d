module kiwi.core.nodefactory;

import kiwi.core.commons;
import kiwi.core.node;
import kiwi.core.nodeinfo;

import kiwi.utils.datastructures : PiecewiseVector;
import kiwi.utils.hstring;

class NodeFactory
{
    alias NodeTypeInfo[uint] NodeTypeArray;
    
    NodeTypeID registerNodeType( NodeTypeInfo info )
    {
        debug{
            log.writeln("registerNodeType: ", info.name);
        }
        assert(info.name.hash != 0);

        foreach( ref i ; _nodeTypes.byKey )
        {
            if( _nodeTypes[i].name == info.name ){
                debug{
                log.writeln("registerNodeType:already registered ");
                log.writeln(" ", info.name );
                }
                return NodeTypeID(i);
            }
        }
        auto newID = NodeTypeID(_nextID++);
        _nodeTypes[newID.index] = info;
        return newID;
    }
    
    bool unregisterNodeType( NodeTypeID type )
    {
        NotImplemented("NodeFactory.unregisternodeType");
        return false;
    }

    const(NodeTypeInfo)* nodeTypeInfo( NodeTypeID id )
    {
        if ( id.index < _nodeTypes.length )
            return &_nodeTypes[id.index];
        return null;
    }

    /**
     * Creates in-place an instance of a given node type.
     * 
     * The inplace Node* parameter must point to a valid uninitialized node 
     * emplacement in memory.
     */ 
    bool instanciateNode( NodeTypeID type, Node* inplace )
    {
        NotImplemented("NodeFactory.instanciateNode");
        return false;
    }
    
private:
    NodeTypeArray _nodeTypes;
    uint _nextID;
}

unittest
{
    import kiwi.utils.testing;
    auto unit = TestSuite("kiwi.core.nodefactory");
    
    import std.stdio;
    DataTypeID intID;
    NodeTypeInfo nti1 = {
        name : HString("Node1"),
        inputs : [
            { HString("in#1"), intID, READ },
            { HString("in#2"), intID, READ }
        ],
        outputs : [
            { HString("out"), intID, READ }
        ]
    };
    NodeTypeInfo nti2 = {
        name : HString("Node2"),
        inputs : [
            { HString("in#2"), intID, READ }
        ],
        outputs : [
            { HString("out"), intID, READ }
        ]
    };

    auto nf = new NodeFactory;

    auto ntid1      = nf.registerNodeType( nti1 );
    auto ntid1bis   = nf.registerNodeType( nti1 );
    auto ntid2      = nf.registerNodeType( nti2 );

    unit.test( ntid1 != ntid2, "Diffenrent registered node types must have different type ids." );
    unit.test( ntid1 == ntid1bis, "Registering th same node type twice should return the same type id" );

    unit.test( nf.nodeTypeInfo(ntid1).name == nti1.name, "Accessing the node type info (1)." );
    unit.test( nf.nodeTypeInfo(ntid2).name == nti2.name, "Accessing the node type info (2)." );

}

