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


#include "DynamicNode.hpp"
#include "kiwi/core/StaticPorts.hpp"

namespace kiwi{
namespace core{



DynamicNode::DynamicNode() : Node() {

}

DynamicNode::DynamicNode( Container* init) {
	ScopedBlockMacro("DynamicNode::constructor(Container*)")
	if(!init) Debug::print() << "warning: the init parameter is nil\n";
	addContainer( init, true, 3 ); // 3 is READ | WRITE access
	_listener = 0;
}

DynamicNode::~DynamicNode() {
	while(nbReaderPorts())
	{
		delete _readerPorts[_readerPorts.size()-1];
		removeReaderPort();
	}
	while(nbWriterPorts())
	{
		delete _writerPorts[_writerPorts.size()-1];
		removeWriterPort();
	}
	while(nbDataPorts())
	{
		delete _dataPorts[_dataPorts.size()-1];
		removeDataPort();
	}
}



portIndex_t DynamicNode::addReaderPort(){
  return addReaderPort( new StaticReaderPort<Container>(this) );
}

portIndex_t DynamicNode::addReaderPort( ReaderPort* port )
{
  if(!port) return -1;
	_readerPorts.push_back( port );
	return _readerPorts.size()-1;
}


portIndex_t DynamicNode::addWriterPort(){
  addWriterPort( new StaticWriterPort<Container>(this) );
}

portIndex_t DynamicNode::addWriterPort( WriterPort* port )
{
  if(!port) return -1;
	_writerPorts.push_back( port );
	return _writerPorts.size()-1;
}


portIndex_t DynamicNode::addDataPort(Container* data, kiwi::uint8_t flags){
  addDataPort( new StaticDataPort<Container>(this, data) ); // TODO flags
}

portIndex_t DynamicNode::addDataPort( DataPort* port )
{
	ScopedBlockMacro("DynamicNode::addDataPort");
	if(!port) return -1;
	// TODO: flags
	_dataPorts.push_back( port );
	return _dataPorts.size()-1;
}


void DynamicNode::addContainer(Container* data, bool addPort, kiwi::uint8_t flags){
	ScopedBlockMacro("DynamicNode::addContainer" )
	if(!data) Debug::error() << "warning: the init parameter is nil\n";
	_containers.add(data);
	if(addPort){
		 addDataPort( new StaticDataPort<>(this, data) ); // TODO flags
	}else{
		Debug::error() << "DynamicNode::addContainer: warning added a container without port\n";
	}
}



void 
DynamicNode::removeReaderPort() {
	_readerPorts.pop_back();
}


void 
DynamicNode::removeWriterPort() {
	_writerPorts.pop_back();
}

void 
DynamicNode::removeDataPort() {
	_dataPorts.pop_back();
}


// ---------------------------------------------------------- Port types


kiwi::utils::Tags 
DynamicNode::readerTags(portIndex_t index) const {
	return kiwi::utils::Tags("#any");
}

kiwi::utils::Tags 
DynamicNode::writerTags(portIndex_t index) const {
	return kiwi::utils::Tags("#any");
}


kiwi::utils::Tags 
DynamicNode::dataTags(portIndex_t index) const {
	return kiwi::utils::Tags("#any");
}


}//namespace core
}//namespace kiwi
