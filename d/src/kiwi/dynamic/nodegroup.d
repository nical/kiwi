module kiwi.dynamic.nodegroup;

import kiwi.core;
import kiwi.commons;
import kiwi.dynamic.node;

import kiwi.graph.traversal;


class NodeGroup : kiwi.core.NodeGroup
{
	enum{ NOT_READY = 0, READY = 1, SORTED = 2, OPTIMIZED = 4 }

	override
	{

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
		
		void update()
		{
			prepare();

			foreach ( node ; _sortedNodes )
			{
				node.update();
			}

			throw new NotImplementedYetException("kiwi.dynamic.nodegroup.NodeGroup.update"
				, __FILE__, __LINE__);
		}
		bool serialize( DataStream stream )
		{
			throw new NotImplementedYetException("kiwi.dynamic.nodegroup.NodeGroup.serialize"
				, __FILE__, __LINE__);
		}
		bool deSerialize( DataStream stream )
		{
			throw new NotImplementedYetException("kiwi.dynamic.nodegroup.NodeGroup.deSerialize"
				, __FILE__, __LINE__);
		}

	}// override

	void prepare()
	{
		_sortedNodes = acyclicOrderedNodes( _nodes );
	}

	bool isReady()
	{
		return (_state & READY);
	}

	int _state;
	Node[] _nodes;
	Node[] _sortedNodes;
}