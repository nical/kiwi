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


#include "Node.hpp"
#include "kiwi/core/ReaderPort.hpp"
#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/WriterPort.hpp"
#include "kiwi/core/DataPort.hpp"

namespace kiwi{
namespace core{



Node::Node()
{
//	Debug::print() << "Node::constructor"<<endl();
	_listener = 0;
}

Node::Node( const NodeInitializer& init)
{
	for( kiwi::uint32_t i = 0; i < init.nbContainers(); ++i){
		addContainer(init.container(i)
				, init.addReader(i)
				, init.addWriter(i) );
	}
	_listener = 0;
}

Node::Node( Container* init)
{
	ScopedBlockMacro(scop,"Node::constructor(Container*)")
	if(!init) Debug::print() << "warning: the init parameter is nil\n";
	addContainer( init, true, true );
	_listener = 0;
}

Node::~Node()
{
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


portIndex_t Node::addReaderPort()
{
//ScopedBlockMacro(scop_b,"addDataPort("+name+")");
//	portIndex_t index = getReaderInputCount();
	_readerPorts.push_back( new ReaderPort(this) );
	return _readerPorts.size()-1;
}


portIndex_t Node::addWriterPort()
{
	_writerPorts.push_back( new WriterPort(this) );
	return _writerPorts.size()-1;
}

portIndex_t Node::addDataPort(Container* data)
{
	_dataPorts.push_back( new DataPort(this, data) );
	return _dataPorts.size()-1;
}

void Node::addContainer(Container* data, bool addPort, kiwi::uint8_t flags)
{
	ScopedBlockMacro(__scop, "Node::addContainer" )
	if(!data) Debug::print() << "warning: the init parameter is nil\n";
	_containers.add(data);
	portIndex_t reader, writer;
	if(addPort){
		 reader = addDataPort(data,flag);
	}
}



void 
Node::removeReaderPort()
{
	_readerPorts.pop_back();
}


void 
Node::removeWriterPort()
{
	_writerPorts.pop_back();
}

void 
Node::removeDataPort()
{
	_dataPorts.pop_back();
}

portIndex_t 
Node::indexOf(const ReaderPort& port) const
{
//ScopedBlockMacro(__scop, "Node::indexOf");
	for(unsigned i = 0; i < _readerPorts.size(); ++i)
		if(_readerPorts[i] == &port)
			return i;
			
	DEBUG_ONLY(
		Debug::error() 
			<< "Node::indexOf( ReaderPort& ) Error : unknown port !" 
			<< endl();
	)//DEBUG_ONLY
		
	//default value
	return 0;	
}

portIndex_t 
Node::indexOf(const WriterPort& port) const
{
//ScopedBlockMacro(__scop, "Node::indexOf");
	for(unsigned i = 0; i < _writerPorts.size(); ++i)
		if(_writerPorts[i] == &port)
			return i;
	DEBUG_ONLY(	
		Debug::error() 
			<< "Node::indexOf( WriterPort& ) Error : unknown port !" 
			<< endl(); 
	)//DEBUG_ONLY
	
	//default value
	return 0;
}


portIndex_t 
Node::indexOf(const DataPort& port) const
{
//ScopedBlockMacro(__scop, "Node::indexOf");
	for(unsigned i = 0; i < _dataPorts.size(); ++i)
		if( _dataPorts[i] == &port )
			return i;
			
	DEBUG_ONLY(
		Debug::error() 
			<< "Node::indexOf( DataPort& ) Error : unknown port !" 
			<< endl();
	)//DEBUG_ONLY
		
	//default value
	return 0;	
}

kiwi::string Node::metaCommand( const kiwi::string& command )
{
	return kiwi::string("kiwi::unknown_command");
}

// ---------------------------------------------------------- port names

/*
kiwi::string 
Node::readerInputName(portIndex_t index) const
{
	return kiwi::string("");
}

kiwi::string 
Node::readerOutputName(portIndex_t index) const
{
	return kiwi::string("");
}

kiwi::string 
Node::writerInputName(portIndex_t index) const
{
	return kiwi::string("");
}

kiwi::string 
Node::writerOutputName(portIndex_t index) const
{
	return kiwi::string("");
}
*/
// ---------------------------------------------------------- Port types


kiwi::Tags 
Node::readerTags(portIndex_t index) const
{
	return kiwi::Tags("#any");
}

kiwi::Tags 
Node::writerTags(portIndex_t index) const
{
	return kiwi::Tags("#any");
}

/*
kiwi::Tags 
Node::DataTags(portIndex_t index) const
{
	return kiwi::Tags("#any");
}
*/
// -------------------------------------------------------- Port binding


void 
Node::bindPort(DataPort& myPort, DataPort& toBind)
{ 
	myPort.bind(toBind); 
}

void 
Node::bindPort(DataPort& myPort, DataPort& toBind)
{ 
	myPort.bind(toBind);
}

void 
Node::bindPort(ReaderPort& myPort, ReaderPort& toBind)
{ 
	myPort.bind(toBind); 
}

void 
Node::bindPort(WriterPort& myPort, WriterPort& toBind)
{ 
	myPort.bind(toBind); 
}


void Node::setPortContainer(DataPort& port, Container* container)
{
	port.setData( container );
}

void Node::setPortContainer(DataPort& port, Container* container)
{
	port.setData( container );
}

// ---------------------------------------------------- Node initializer


void NodeInitializer::addContainer(Container* theContainer, bool hasReader, bool hasWriter)
{
	ContainerInit n;
	n.container = theContainer;
	n.addReader = hasReader;
	n.addWriter = hasWriter;
	_data.add( n );
}

kiwi::uint32_t NodeInitializer::nbContainers() const
{
	return _data.size();
}

Container* NodeInitializer::container(kiwi::uint32_t index) const
{
	return _data[index].container;
}

bool NodeInitializer::addReader(kiwi::uint32_t index) const
{
	return _data[index].addReader;
}

bool NodeInitializer::addWriter(kiwi::uint32_t index) const
{
	return _data[index].addWriter;
}

// ----------------------------------------------------------- Operators


bool 
operator >> (DataPort& output, ReaderPort& input )
{
	ScopedBlockMacro(scop, "operator >> (reader)" )
	if(!input.isConnected())
	{
		return input.connect(output);
	}else{return false;}
}

bool 
operator >> (DataPort& output, WriterPort& input )
{
	ScopedBlockMacro(scop, "operator >> (writer)" )
	if(!input.isConnected())
	{
		input.connect(output);
		return true;
	}else{return false;}
}




}//namespace core
}//namespace kiwi
