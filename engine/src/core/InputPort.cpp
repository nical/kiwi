// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



//#include "Node.hpp"

namespace kiwi
{
namespace core	
{

template class Node::InputPort<Reader>;
template class Node::InputPort<Writer>;

// ----------------------------------------------------------- InputPort
template <typename SlotType>
Node::InputPort<SlotType>::InputPort( Node* myNode )
:   _connectedNode(0)
	, _enabled(true)
	, _subPort(0)
	, _node(myNode)
{
	//nothing to do
}


template <typename SlotType>
void 
Node::InputPort<SlotType>::connect(OutputPort<SlotType>& outputPort, bool isMetaPort)
{
ScopedBlockMacro(__sccop, "Node::InputPort<SlotType>::connect" );
	if( !isEnabled() )
	{
		Debug::error() << "InputPort::connect() : input port disabled" << endl();
		return;
	}
	if( !outputPort.isEnabled() )
	{
		Debug::error() << "InputPort::connect() : output port disabled" << endl();
		return;
	}
	// if it is the subPort
	
		if(isCompatible(outputPort) )
		{
			if( isConnected() ) disconnect();
			_connectedNode = &outputPort;
			if( isMetaPort ) outputPort._connections.push_back(this);
			if( _subPort != 0 )	_subPort->connect(outputPort, false);
			if( _node->isLayoutEventEnabled() ) 
					_node->layoutChanged();
		}
		else
		{
			Debug::error() << "InputPort::connect() : uncompatible ports - connection failed" << endl();
			Debug::error() << outputPort.type() << " >> " << type() << endl();
			return;
		}
	
}

template <typename SlotType>
void 
Node::InputPort<SlotType>::disconnect()
{
ScopedBlockMacro(scp_block,"Node::InputPort<SlotType>::disconnect");
	if(_subPort != 0) _subPort->disconnect();
	if(!isConnected() ) return;
	for(typename OutputPort<SlotType>::connectionList::iterator it
		= _connectedNode->_connections.begin(); it!= _connectedNode->_connections.end(); ++it)
	{
		if(*it == this)
		{
			_connectedNode->_connections.erase(it);
			break;
		}
	}
	_connectedNode= 0;
}


template <typename SlotType>
void 
Node::InputPort<SlotType>::bind(InputPort<SlotType>& port)
{
DEBUG_ONLY(	Debug::print() << "input port rebinding" << endl();  )
	_subPort = &port;
	// note that if the binded Node is deleted, trying to acces
	// this port might cause a segfault
}


template <typename SlotType>
inline portIndex_t 
Node::InputPort<SlotType>::index() const 
{
	return _node->indexOf(*this);
}

template <typename SlotType>
inline Node* 
Node::InputPort<SlotType>::node() const 
{
	return _node;
}

template <typename SlotType>
Node::InputPort<SlotType>* 
Node::InputPort<SlotType>::subPort()
{
	// if there's port rebinding, _subPort != 0 
	// call the _subPort's method
	if(_subPort) return _subPort->subPort();
	// if this is the "subport" return a pointer to self
	else return this;
} 


template<>
string 
Node::InputPort<Reader>::type() 
{
	return subPort()->node()->readerInputType( index() );
}

template<>
string 
Node::InputPort<Writer>::type() 
{ 
	return subPort()->node()->writerInputType( index() ); 
}

template <typename SlotType>
inline bool 
Node::InputPort<SlotType>::isCompatible(OutputPort<SlotType>& output)	
{ 
	return ( (type().find(output.type())!= string::npos) 
		|| (type().find("any")!= string::npos) );
}

template <typename SlotType>
inline bool 
Node::InputPort<SlotType>::isConnected() const 
{ 
	return (_connectedNode != 0); 
}

template <typename SlotType>
inline bool 
Node::InputPort<SlotType>::isEnabled() const 
{
	return _enabled;
}

template <typename SlotType>
inline Node::OutputPort<SlotType>* 
Node::InputPort<SlotType>::connectedOutput() const 
{ 
	return _connectedNode; 
}


template<>
kiwi::string 
Node::InputPort<Reader>::name()
{
	return _node->readerInputName(_node->indexOf(*this));
}

template<>
kiwi::string 
Node::InputPort<Writer>::name()
{
	return _node->readerInputName(_node->indexOf(*this));
}




// ----------------------------------------------------------- protected



template <typename SlotType>
inline void 
Node::InputPort<SlotType>::setEnabled(bool status) 
{
	_enabled = status;
}

/*
template <typename SlotType>
inline void 
Node::InputPort<SlotType>::setType(const string& type)
{
	_type = type;
}

*/



} //namespace
} //namespace