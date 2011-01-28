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


namespace kiwi{
namespace core{



ReaderOutputPort::ReaderOutputPort( Node* myNode )
	: _enabled(true)
	, _node(myNode)
{
	// nothing to do
}

/*
const ReaderOutputPort* 
ReaderOutputPort::subPort() const
{
	// if there's port rebinding, _subPort 1!= 0 
	// call the _subPort's method
	if(_subPort) return _subPort->subPort();
	// if this is the "subport" return a pointer to self
	else return this;
} 
*/
/*
void 
ReaderOutputPort::disconnect( ReaderInputPort* input )
{
//	ScopedBlockMacro(__scop, "OutputPort::disconnect" );
	if( input == 0 ){
		std::list<ReaderInputPort*> connectionsTempCopy
			= _connections;
		_connections.clear();
		std::list<ReaderInputPort*>::iterator
			it = connectionsTempCopy.begin();

		for(int i = 0; i < connectionsTempCopy.size(); ++i)
		{
			ReaderInputPort* temp = (*it);
			connectionsTempCopy.erase(it);
			temp->disconnect();
			++it;
		}

	}else
		for(std::list<ReaderInputPort*>::iterator
			it = _connections.begin()
			; it!= _connections.end()
			; ++it)
		{
			if( (*it) == input ){
				_connections.erase(it);
				input->disconnect();
				return;
			}
		}
}
*/


void 
ReaderOutputPort::bind(ReaderOutputPort& port)
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


kiwi::string 
ReaderOutputPort::name() const
{
	return _node->readerOutputName( _node->indexOf(*this) );
}


portIndex_t 
ReaderOutputPort::index() const 
{
	return _node->indexOf(*this);
}


Node* 
ReaderOutputPort::node() const 
{
	return _node;
}


Tags 
ReaderOutputPort::tags() const
{ 
	return _node->readerOutputTags( index() ); 
}


bool 
ReaderOutputPort::isCompatible(ReaderInputPort& input)	
{
	return input.isCompatible(*this); 
}


bool ReaderOutputPort::connect(ReaderInputPort& inputPort)
{
	return connect( &inputPort);
}


/*
bool 
ReaderOutputPort::isConnected() const 
{ 
	return (_connections.size() != 0); 
}
*/

bool 
ReaderOutputPort::isEnabled() const 
{ 
	return _enabled; 
}

/*
ReaderOutputPort::connectionList 
ReaderOutputPort::connections() const 
{ 
	return _connections; 
}
*/


void 
ReaderOutputPort::setEnabled(bool status) 
{
	_enabled = status;
}

}// namespace
}// namespace
