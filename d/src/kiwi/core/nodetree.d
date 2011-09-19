module kiwi.core.nodetree;

import kiwi.core.commons;
import kiwi.core.node;

class NodeTree
{
    enum{ SEQUENTIAL, CONCURRENT };

    @property
    {
        int execution()
        {
            return _type;
        }
        bool isRoot()
        {
            return _parent is null;
        }
        bool isLeaf()
        {
            return _children.length == 0;
        }
        NodeTree[] children()
        {
            return _children;
        }
        
        NodeTree parent()
        {
            return _parent;
        }

        NodeTree root()
        {
            if( isRoot ) return this;
            else return parent.root;
        }   
        
        Node[] nodes()
        {
            if( isLeaf )
                return _nodes;

            Node[] result;
            foreach( child ; _children )
                result ~= child.nodes;
            return result;
        }
    }

    void update()
    {
        foreach( n ; nodes )
            n.update();
    }

package:
    NodeTree    _parent;
    NodeTree[]  _children;
    Node[]      _nodes;
    int         _type;
} 
