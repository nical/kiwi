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

#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/ReaderPort.hpp"
#include "kiwi/core/WriterPort.hpp"

#include "kiwi/core/Container.hpp"

namespace kiwi{
namespace core{


/*
DataPort::DataPort( Node* myNode, Container* data )
	:_node(myNode)
{
	ScopedBlockMacro("DataPort::constructor")
	if(!data){
		Debug::print() << "DataPort::constructor: warning: data = 0\n";
	}
	setAbstractContainer(data);
}
*/
DataPort::DataPort( Node* myNode )
	:_node(myNode), _masterLinkedDataPort(0)
{
	ScopedBlockMacro("DataPort::constructor")
}


void DataPort::bind(DataPort& port)
{
  ScopedBlockMacro("DataPort::bind")
  unbind();
//	Debug::print() << "port binding" << endl();
	
  _masterLinkedDataPort = &port;
  port._slaveLinkedDataPorts.add( this );
  setAbstractContainer( port.getAbstractContainer() );
}

void DataPort::unbind()
{
  ScopedBlockMacro("DataPort::unbind")
	for(kiwi::uint32_t i = 0; i < _slaveLinkedDataPorts.size(); ++i )
		_slaveLinkedDataPorts[i]->unBind();

  if(_masterLinkedDataPort)
    _masterLinkedDataPort->_slaveLinkedDataPorts.remove(this);

  _masterLinkedDataPort = 0;
	//_container = 0; TODO !!!
}


portIndex_t DataPort::index() const 
{
	return _node->indexOf(*this);
}

bool  DataPort::isComposite() const{
	return (_subPorts.size() > 1 );
}

Node* DataPort::node() const 
{
	return _node;
}


utils::Tags DataPort::tags() const
{
	if( !isEmpty() ){
		return getAbstractContainer()->tags(); 
	}else{
		Debug::error() << "DataPort::tags: warning: no container available\n"; 
		return utils::Tags("#undefined");
	}
}


bool DataPort::isCompatible(ReaderPort& input){
  ScopedBlockMacro("DataPort::isCompatible")
	return input.isCompatible(*this); 
}

bool DataPort::isCompatible(WriterPort& input){
	return input.isCompatible(*this); 
}

bool DataPort::connect(ReaderPort* inputPort)
{
	ScopedBlockMacro( "DataPort::connect" )
  if( inputPort != 0 ){
    inputPort->connect( this );
  } else return false;
}


bool DataPort::connect(WriterPort* inputPort)
{
  ScopedBlockMacro( "DataPort::connect" )
  if( inputPort != 0 ){
    inputPort->connect( this );
  }
  else return false;
}

void DataPort::disconnectReader( ReaderPort* port ){
  if( isConnectedToReader( port ) ){
    port->disconnect( this );
  }
}

void DataPort::disconnectWriter( WriterPort* port ){
  if( isConnectedToWriter( port ) ){
    port->disconnect(this);
  }
}


bool DataPort::isEnabled() const //TODO
{ 
	//return _container != 0; 
	return true; 
}




void DataPort::connect_impl( ReaderPort* port ){
  _connectedReaders.add( port );
}

void DataPort::disconnect_impl( ReaderPort* port ){
  _connectedReaders.remove( port );
}

void DataPort::connect_impl( WriterPort* port ){
  _connectedWriters.add( port );
}

void DataPort::disconnect_impl( WriterPort* port ){
  _connectedWriters.remove( port );
}

void DataPort::connectWithoutChecking( ReaderPort* port ){
    port->connectWithoutChecking( this );
}

void DataPort::connectWithoutChecking( WriterPort* port ){
    port->connectWithoutChecking( this );
}



namespace internals{
  void callBindPort(DataPort& p1, DataPort& p2){
    p1.bind(p2);
  }
}//namespace internals


}// namespace
}// namespace
