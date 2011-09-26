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


// -----------------------------------------

/*



   P: parallel
   S: sequential
   * b.depends(a): b has a parent that depends on a parent of a (after a in sequence)
   * if b is sequential and a is sequential and a direct child of b,
            then a should be merged into b
   * a child of a seq nodeTree is a parallel nodeTree 
   
  
   Connect(Node a, Node b)
   {
       if( a.fullDependencies.contains b )
          return false ;
       if(a.nodeTree is b.nodeTree)
          return true;
       sequentialMerge(a.nodeTree, b.nodeTree);
   }
  
   sequentialMerge(NodeTree a, NodeTree b)
   {
       if( a.root is b.root && b.depends(a) )
            return true;
   }

   
*/
