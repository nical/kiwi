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

#include "kiwi/core/Reader.hpp"
#include "kiwi/core/Writer.hpp"

#include "kiwi/core/ReaderOutputPort.hpp"
#include "kiwi/core/ReaderInputPort.hpp"

#include "kiwi/core/Container.hpp"

namespace kiwi{
namespace core{



ReaderOutputPort::ReaderOutputPort( Node* myNode, Container* data )
	: _enabled(true)
	, _node(myNode)
	, _container(data)
{
	// nothing to do
}


void ReaderOutputPort::bind(ReaderOutputPort& port)
{
//	Debug::print() << "port binding" << endl();
	_container = port._container;
	port._linkedOutputPorts.add( this );

	// note that if the binded Node is deleted, trying to acces
	// this port might cause a segfault
}

void ReaderOutputPort::unBind()
{
	for(kiwi::uint32_t i = 0; i < _linkedOutputPorts.size(); ++i )
		_linkedOutputPorts[i]->unBind();
		
	_container = 0;
}

void ReaderOutputPort::setData( Container* data )
{
	for(kiwi::uint32_t i = 0; i < _linkedOutputPorts.size(); ++i )
		_linkedOutputPorts[i]->setData( data );

	_container = data;
}


kiwi::string ReaderOutputPort::name() const
{
	return _node->readerOutputName( _node->indexOf(*this) );
}


portIndex_t ReaderOutputPort::index() const 
{
	return _node->indexOf(*this);
}


Node* ReaderOutputPort::node() const 
{
	return _node;
}


Tags ReaderOutputPort::tags() const
{
	if(_container){
		return _container->tags(); 
	}else{		// TODO : The following call may be removed in the future
		return _node->readerOutputTags( index() );
	}
}


bool ReaderOutputPort::isCompatible(ReaderInputPort& input)	
{
	return input.isCompatible(*this); 
}


bool ReaderOutputPort::connect(ReaderInputPort& inputPort)
{
	ScopedBlockMacro( __scop, "ReaderOutputPort::connect" )
	if( isEnabled() && inputPort.isEnabled() ){
		if( isCompatible( inputPort ) )
			return PortConnector::connect( &inputPort);
	}
	else return false;
}

bool ReaderOutputPort::connect(ReaderInputPort* inputPort)
{
	ScopedBlockMacro( __scop, "ReaderOutputPort::connect" )
	if( (inputPort != 0) && (isEnabled() && inputPort->isEnabled()) ){
		if( isCompatible( *inputPort ) )
			return PortConnector::connect( inputPort );
	}
	else return false;
}



bool ReaderOutputPort::isEnabled() const 
{ 
	return _enabled; 
}


void ReaderOutputPort::setEnabled(bool status) 
{
	_enabled = status;
}

}// namespace
}// namespace
