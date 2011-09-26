module kiwi.core.nodegroup;

import kiwi.core.commons;
import kiwi.core.node;

interface NodeProcessor
{
    void update( NodeGroup group );
}

class NodeGroup
{
    void update( NodeProcessor p)
    {
        p.update( this );
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
        if ( !contains(n) )
            _nodes ~= n;
        foreach( dep ; n.previousNodes )
            recursiveAddNode( dep );
        foreach( fol ; n.nextNodes )
            recursiveAddNode( fol );
        
    }

    bool isValid()
    {
        return true; //TODO
    }

    bool contains( Node node )
    {
        foreach( n ; _nodes )
            if ( n is node )
                return true;
        return false;
    }
    

    private Node[] _nodes;
}
