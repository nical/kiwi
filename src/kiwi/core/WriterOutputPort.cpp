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
#include "kiwi/core/Container.hpp"

#include "kiwi/core/Writer.hpp"
#include "kiwi/core/Writer.hpp"

#include "kiwi/core/WriterOutputPort.hpp"
#include "kiwi/core/WriterInputPort.hpp"


namespace kiwi{
namespace core{



WriterOutputPort::WriterOutputPort( Node* myNode, Container* data )
	: _node(myNode)
	, _associatedReaderOutputPort(0)
{
	ScopedBlockMacro(scop, "WriterOutputPort::constructor")
	if(!data){
		Debug::print() << "WriterOutputPort::constructor: warning: data = 0\n";
	}
	setData(data);
}


void WriterOutputPort::bind(WriterOutputPort& port)
{
	_container = port._container;
	port._linkedOutputPorts.add( this );
}

void WriterOutputPort::unBind()
{
	for(kiwi::uint32_t i = 0; i < _linkedOutputPorts.size(); ++i )
		_linkedOutputPorts[i]->unBind();
		
	_container = 0;
}

void WriterOutputPort::setData( Container* data )
{
	ScopedBlockMacro(scop,"WriterOutputPort::setData")
	if(!data) Debug::print() << "warning: param data = 0\n";
	for(kiwi::uint32_t i = 0; i < _linkedOutputPorts.size(); ++i )
		_linkedOutputPorts[i]->setData( data );

	_container = data;
	if( data->isComposite() ){
		Debug::print() << "the data is composite ("<<data->nbSubContainers()<<")\n"; 
		for(kiwi::uint32_t i = 0; i < data->nbSubContainers(); ++i){
			_subPorts.add(new WriterOutputPort(_node, data->subContainer(i)));
		}
	}
}

bool  WriterOutputPort::isComposite() const{
	return (_subPorts.size() > 1 );
}

kiwi::string WriterOutputPort::name() const
{
	return _node->writerOutputName( _node->indexOf(*this) );
}


portIndex_t WriterOutputPort::index() const 
{
	return _node->indexOf(*this);
}


Node* WriterOutputPort::node() const 
{
	return _node;
}


Tags WriterOutputPort::tags() const
{ 
	if(_container){
		return _container->tags(); 
	}else{
		Debug::error() << "WriterOutputPort::tags: warning: no container available\n"; 
		return Tags("#undefined");
	}
}


bool WriterOutputPort::isCompatible(WriterInputPort& input)	
{
	return input.isCompatible(*this); 
}


bool WriterOutputPort::connect(WriterInputPort& inputPort)
{
	ScopedBlockMacro(scop, "WriterOutputPort::connect" )
	if( isEnabled() && inputPort.isEnabled() ){
		if( isCompatible( inputPort ) )
			return PortConnector::connect( &inputPort);
	}
	else return false;
}

bool WriterOutputPort::connect(WriterInputPort* inputPort)
{
	ScopedBlockMacro(scop, "WriterOutputPort::connect" )
	if( (inputPort != 0) && (isEnabled() && inputPort->isEnabled()) ){
		if( isCompatible( *inputPort ) )
			return PortConnector::connect( inputPort );
	}
	else return false;
}


bool WriterOutputPort::isEnabled() const 
{ 
	_container != 0; 
}

}// namespace
}// namespace
