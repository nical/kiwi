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

#include "kiwi/core/Node.hpp"

#include "kiwi/core/Writer.hpp"
#include "kiwi/core/Writer.hpp"

#include "kiwi/core/WriterPort.hpp"
#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/Container.hpp"


namespace kiwi{
namespace core{


// ----------------------------------------------------------- InputPort

WriterPort::WriterPort( Node* myNode )
:	_enabled(true)
	, _node(myNode)
	, _associatedDataPort(0)
{
	
}


bool WriterPort::connect(DataPort& outputPort)
{
	ScopedBlockMacro( __scop, "WriterPort::connect" )
	if( isEnabled() && outputPort.isEnabled() ){
		if( isCompatible( outputPort.tags() ) ){
			bool status = PortConnector::connect( &outputPort );
			if(status && _associatedDataPort)
				_associatedDataPort->setContainer(
					outputPort.getContainer<Container>() );
			return status;
		}else{
			Debug::error() << "WriterPort::connect: uncompatible port tags\n";	
			return false;
		}
	}else{
		Debug::error() << "ReaderPort::connect error: one of the port is disabled!" << endl();
		return false;
	}
}

bool WriterPort::connect(DataPort* outputPort)
{
	assert(false);
	ScopedBlockMacro( __scop, "WriterPort::connect" )
	if( (outputPort!=0) && isEnabled() && outputPort->isEnabled() )
		if( isCompatible( *outputPort ) )
			return PortConnector::connect( outputPort );
	else return false;
}


void 
WriterPort::bind(WriterPort& port)
{
//DEBUG_ONLY( Debug::print() << "input port rebinding" << endl(); )
	port._linkedInputPorts.add(&port);
	
}



portIndex_t 
WriterPort::index() const 
{
	return _node->indexOf(*this);
}


Node* 
WriterPort::node() const 
{
	return _node;
}



Tags WriterPort::tags() const
{
	return node()->writerTags( index() );
}

bool WriterPort::isCompatible(DataPort& output)	
{ 
	return ( tags().hasOneOf(output.tags()+Tags("#any") ) );
}


bool WriterPort::isCompatible(const kiwi::Tags& tag)	
{ 
	return ( tags().hasOneOf(tag + Tags("#any") ) );
}

/*
bool 
WriterPort::isConnected() const 
{ 
	return (_connectedNode != 0); 
}
*/

bool 
WriterPort::isEnabled() const 
{
	return _enabled;
}


DataPort* 
WriterPort::connectedPort() const 
{ 
	return PortConnector::connectedInstance(0);
}


kiwi::string 
WriterPort::name() const
{
//	return _node->writerInputName(_node->indexOf(*this)); TODO
}





// ----------------------------------------------------------- protected




void 
WriterPort::setEnabled(bool status) 
{
	_enabled = status;
}



} //namespace
} //namespace
