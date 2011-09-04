module kiwi.dynamic.nodegroup;

import kiwi.core.base;
import kiwi.core.commons;
import kiwi.core.data;
import kiwi.dynamic.node;

import kiwi.graph.acyclic;

class InternalInputPort : InputPort
{
	this()
	{
		super(null);
	}
}

class InternalOutputPort : OutputPort
{
	this(InputPort linkedInput)
	in{	assert( linkedInput !is null ); }
	body
	{
		super(null);
		_linkedInput = linkedInput;
	}

	override
	{
        @property
        {
            int maxConnections() { return -1; }
            string name() { return _linkedInput.name; }
            OutputPort[] subPorts() 
            {
            	throw NotImplemented("NodeGroup.subPorts");
            }
            DataTypeInfo dataType() pure 
            { 
	            throw NotImplemented("NodeGroup.dataType"); 
	        }
            Data data()
            {
            	throw NotImplemented("NodeGroup.data");
            }
        }

        bool isComposite()
        {
        	throw NotImplemented("NodeGroup.isComposite"); 
        }
        bool isCompatible( InputPort port ){ return (port !is null); }         
                   
    }
    @property void data( kiwi.core.base.Data value )
    {
    	throw NotImplemented("NodeGroup.data:set"); 
    }
private:
	InputPort _linkedInput;
}

class NodeGroup : kiwi.core.base.NodeGroup
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

			throw NotImplemented("kiwi.dynamic.nodegroup.NodeGroup.update");			
		}
		bool serialize( DataStream stream )
		{
			throw NotImplemented("kiwi.dynamic.nodegroup.NodeGroup.serialize");
		}
		bool deSerialize( DataStream stream )
		{
			throw NotImplemented("kiwi.dynamic.nodegroup.NodeGroup.deSerialize");
		}

	}// override

	void prepare()
	{
		_sortedNodes = OrderedNodes( _nodes );
	}

	bool isReady()
	{
		return (_state & READY);
	}

	int _state;
	Node[] _nodes;
	Node[] _sortedNodes;
}