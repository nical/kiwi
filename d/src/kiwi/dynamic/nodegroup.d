module kiwi.dynamic.nodegroup;

import kiwi.core.base;
import kiwi.core.commons;
import kiwi.core.data;
import kiwi.dynamic.node;
import kiwi.dynamic.port;
import kiwi.dynamic.compatibility;

import kiwi.graph.acyclic;


class MetaNode : DynamicNode
{
	this( NodeGroup group )
	{	
		super([],[],null);	
		_nodeGroup = group;
	}

	override
	{
		void update()
		{
			_nodeGroup.update();
		}

		void addInputPort( PortCompatibility compatibility, int flags, string name)
		{
			_nodeGroup.addInput( name );
			super.addInputPort( compatibility, flags, name);
		}
	}

	NodeGroup nodeGroup() pure
	{
		return _nodeGroup;
	}

private:	
	NodeGroup _nodeGroup;
}

class NodeGroup : kiwi.core.base.NodeGroup
{		
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
			if ( !isReady ) prepare();

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
		throw NotImplemented("NodeGroup.isReady");
	}

	/++
	 + add an input to this group and create an output port to which will connect the nested nodes' input.
	 +/
	void addInput( string name = "in" )
	{
		// TODO: better DataType support !
		_inputBridge ~= new DynamicOutputPort(null, null, null, name);
	}

	void removeInput()
	{
		_inputBridge.length -= 1;
	}

	void addOutput( int flags = 0, string name = "out")
	{
		_outputBridge ~= new DynamicInputPort( null, new AlwaysCompatible, flags, name );
	}

	void removeOutput()
	{
		_outputBridge.length -= 1;
	}


private:

	int _state;
	OutputPort[] _inputBridge;
	InputPort[] _outputBridge;
	Node[] _nodes;
	Node[] _sortedNodes;
}



//              #######   #####    ####   #####    ####
//                 #      #       #         #     #   
//                 #      ###      ###      #      ### 
//                 #      #           #     #         #
//                 #      #####   ####      #     #### 



version(unittest){ import kiwi.utils.mock; }

unittest
{
	mixin( logTest!"kiwi.dynamic.nodegroup" );

	auto metaNode = new MetaNode( new NodeGroup );

	auto n1 = NewMockNode(1,1);
	auto n2 = NewMockNode(1,1);
	auto before = NewMockNode(0,1);

	metaNode.nodeGroup.addNode(n1);
	metaNode.nodeGroup.addNode(n2);

	metaNode.addInputPort(new AlwaysCompatible, 0, "input" );

	n1.output() >> n2.input();
	before.output() >> metaNode.input();


    //auto internal = new InternalOutputPort;
}
