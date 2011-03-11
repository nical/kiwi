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


namespace kiwi{
namespace core{


// ----------------------------------------------------------- InputPort

ReaderPort::ReaderPort( Node* myNode )
:	_enabled(true), _node(myNode), _connectedDataPort(0)
{
	//nothing to do
}


bool ReaderPort::connect(DataPort* port)
{
	ScopedBlockMacro( __scop, "ReaderPort::connect*" )
  
	if( (port!=0) && isEnabled() && port->isEnabled() )
		if( isCompatible( *port ) ){
      disconnect();//only one connection at a time
      connect_impl( port );
      port->connect_impl( this );
      updatePort();
			return true;
    }
	else return false;
}


void ReaderPort::bind(ReaderPort& port)
{
DEBUG_ONLY( Debug::print() << "reader port binding" << endl(); )
	port._linkedInputPorts.add(&port);
}



portIndex_t ReaderPort::index() const 
{
	return _node->indexOf(*this);
}


Node* ReaderPort::node() const 
{
	return _node;
}


Tags ReaderPort::tags() const
{
	ScopedBlockMacro(scop,"ReaderPort::tags")
	return node()->readerTags( index() );
}

bool ReaderPort::isCompatible(DataPort& output)	
{
	ScopedBlockMacro(scop, "ReaderPort::isCompatible");
	return ( tags().hasOneOf(output.tags()+Tags("#any") ) );
}


bool ReaderPort::isCompatible(const kiwi::Tags& tag)	
{
	ScopedBlockMacro(scop, "ReaderPort::isCompatible");
	return ( tags().hasOneOf(tag + Tags("#any") ) );
}

bool ReaderPort::isEnabled() const 
{
	return _enabled;
}


DataPort* ReaderPort::connectedPort() const 
{ 
	return _connectedDataPort;
}

bool ReaderPort::isConnected( DataPort* port ) const {
  if(port) return connectedPort() == port;
  else return connectedPort() != 0;
}

bool ReaderPort::disconnect( DataPort* port ){
if(port){
    if( isConnected( port ) ){
      disconnect_impl(0);
      port->disconnect_impl(this);
      return true;
    }else return false;
  }else{
    if( isConnected() ){
      disconnect_impl(0);
      connectedPort()->disconnect_impl(this);
      return true;
    }else return false;
  }
}


// ----------------------------------------------------------- protected


void ReaderPort::connect_impl( DataPort* port ){
  _connectedDataPort = port;
}

void ReaderPort::disconnect_impl( DataPort* port ){
  _connectedDataPort = 0;
}


void 
ReaderPort::setEnabled(bool status) 
{
	_enabled = status;
}



} //namespace
} //namespace
