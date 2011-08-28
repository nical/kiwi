module kiwi.dynamic.nodegroup;

import kiwi.core;
import kiwi.commons;
import kiwi.dynamic.node;


class NodeGroup : kiwi.core.NodeGroup
{
	override{
		bool addNode( Node n )
		{
			_nodes ~= n;
			return true;
		}
		bool removeNode( Node n )
		{
			for(int i = 0; i < _nodes.length; ++i)
				if ( _nodes[i] is n )
				{
					_nodes[i] = _nodes[$-1];
					return true;
				}
			return false;
		}
		void optimize( int flags ){};
		void update(){};
		bool serialize( DataStream stream ){ return false; }
		bool deSerialize( DataStream stream ){ return false; }
	}


	Node[] _nodes;
}