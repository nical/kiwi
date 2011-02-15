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

#include "kiwi/core/WriterOutputPort.hpp"
#include "kiwi/core/WriterInputPort.hpp"
#include "kiwi/core/ReaderOutputPort.hpp"


namespace kiwi{
namespace core{


// ----------------------------------------------------------- InputPort

WriterInputPort::WriterInputPort( Node* myNode )
:	_enabled(true)
	, _node(myNode)
	, _associatedReaderOutputPort(0)
{
	//nothing to do
	//(everything is in the initialization above)
}


bool WriterInputPort::connect(WriterOutputPort& outputPort)
{
	ScopedBlockMacro( __scop, "WriterInputPort::connect" )
	if( isEnabled() && outputPort.isEnabled() )
		if( isCompatible( outputPort.tags() ) ){
			if( _associatedReaderOutputPort ){
				_associatedReaderOutputPort->bind(
					*outputPort.associatedReaderOutputPort() );
			}	
			return PortConnector::connect( &outputPort );
		}else return false;
	else return false;
}

bool WriterInputPort::connect(WriterOutputPort* outputPort)
{
	ScopedBlockMacro( __scop, "WriterInputPort::connect" )
	if( (outputPort!=0) && isEnabled() && outputPort->isEnabled() )
		if( isCompatible( *outputPort ) )
			return PortConnector::connect( outputPort );
	else return false;
}


void 
WriterInputPort::bind(WriterInputPort& port)
{
//DEBUG_ONLY( Debug::print() << "input port rebinding" << endl(); )
	port._linkedInputPorts.add(&port);
	
}



portIndex_t 
WriterInputPort::index() const 
{
	return _node->indexOf(*this);
}


Node* 
WriterInputPort::node() const 
{
	return _node;
}



Tags WriterInputPort::tags() const
{
	return node()->writerInputTags( index() ); // TODO (subport ?)
}

bool WriterInputPort::isCompatible(WriterOutputPort& output)	
{ 
	return ( tags().hasOneOf(output.tags()+Tags("any") ) );
}


bool WriterInputPort::isCompatible(const kiwi::Tags& tag)	
{ 
	return ( tags().hasOneOf(tag + Tags("any") ) );
}

/*
bool 
WriterInputPort::isConnected() const 
{ 
	return (_connectedNode != 0); 
}
*/

bool 
WriterInputPort::isEnabled() const 
{
	return _enabled;
}


WriterOutputPort* 
WriterInputPort::connectedOutput() const 
{ 
	return PortConnector::connectedInstance(0);
}


kiwi::string 
WriterInputPort::name() const
{
	return _node->writerInputName(_node->indexOf(*this));
}





// ----------------------------------------------------------- protected




void 
WriterInputPort::setEnabled(bool status) 
{
	_enabled = status;
}



} //namespace
} //namespace
