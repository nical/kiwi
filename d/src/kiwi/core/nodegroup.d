module kiwi.core.nodegroup;

import kiwi.core.commons;
import kiwi.core.node;

interface NodeProcessor
{
    bool update( NodeGroup group );
}

class NodeGroup
{
    this()
    {
        _nodes = [];
    }
    
    @property
    {
        Node[] nodes()
        {
            return _nodes;
        }
    }

    bool addNode( Node n )
    {
        if ( contains(n) )
            return false;
        _nodes ~= n;
        return true;
    }

    void recursiveAddNode( Node n )
    {
        mixin( logFunction!"NodeGroup.recursiveAddNode" );
        if ( !contains(n) )
            _nodes ~= n;
    
        foreach( dep ; n.previousNodes )
            if ( !contains(dep) )
            {
                log.foo;
                _nodes ~= dep;
                recursiveAddNode( dep );
            }
               
        foreach( fol ; n.nextNodes )
            if ( !contains(fol) )
            {
                log.bar;
                _nodes ~= fol;
                recursiveAddNode( fol );
            }
    }

    bool isValid()
    {
        throw NotImplemented("NodeGroup.isValid");
    }

    bool contains( Node node_ )
    {
        mixin( logFunction!"NodeGroup.contains" );
        foreach( ref n ; _nodes ){
            if ( n is node_ )
            {
                return true;
            }
        }
        log.writeDebug(3,"false");
        return false;
    }
    

    private Node[] _nodes;
}





//            #####   #####    ####   #####    ####
//              #     #       #         #     #
//              #     ###      ###      #      ###
//              #     #           #     #         #
//              #     #####   ####      #     ####






version(unittest)
{
    import kiwi.core.mock;
}

unittest
{
    auto n1 = NewMockNode(1,1);
    auto n2 = NewMockNode(1,1);
    auto n3 = NewMockNode(2,1);
    auto n4 = NewMockNode(1,1);
    
    assert( n3.previousNodes.length == 0 );

    assert( n1.output(0) >> n3.input(0) );
    assert( n2.output(0) >> n3.input(1) );
    assert( n3.output(0) >> n4.input(0) );
    assert( n1.output(0).isConnected() );
    assert( n1.output(0).connections.length == 1 );
    assert( n2.output(0).connections.length == 1 );
    log.writeln("n1.nextNodes.length ", n1.nextNodes.length );
    assert( n1.nextNodes.length == 1 );
    assert( n2.nextNodes.length == 1 );
    assert( n1.previousNodes.length == 0 );
    assert( n2.previousNodes.length == 0 );
    assert( n3.previousNodes.length == 2 );
    assert( n4.previousNodes.length == 1 );

    auto g = new NodeGroup;

    assert( !g.contains(n1) );
    assert( !g.contains(n2) );
    assert( !g.contains(n3) );
    assert( !g.contains(n4) );
    
    g.recursiveAddNode(n3);
    log.writeln("g.nodes.length ", g.nodes.length );

    assert( g.contains(n1) );
    assert( g.contains(n2) );
    assert( g.contains(n3) );
    assert( g.contains(n4) );
    

    foreach( n ; g.nodes )
    {
        if( n is n1 ) log.writeln("n1");
        if( n is n2 ) log.writeln("n2");
        if( n is n3 ) log.writeln("n3");
        if( n is n4 ) log.writeln("n4");
    }
    assert( g.nodes.length == 4 );
    
}
