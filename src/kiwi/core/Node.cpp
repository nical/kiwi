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
#include "kiwi/core/ReaderInputPort.hpp"
#include "kiwi/core/ReaderOutputPort.hpp"
#include "kiwi/core/WriterInputPort.hpp"
#include "kiwi/core/WriterOutputPort.hpp"

namespace kiwi{
namespace core{



Node::Node()
{
//	Debug::print() << "Node::constructor"<<endl();
	_listener = 0;
}

Node::~Node()
{
//	Debug::print() << "Node::destructor"<<endl();
	while(nbReaderInputs())
	{
		delete _readerInputs[_readerInputs.size()-1];
		removeReaderInputPort();
	}
	while(nbReaderOutputs())
	{
		delete _readerOutputs[_readerOutputs.size()-1];
		removeReaderOutputPort();
	}
	while(nbWriterInputs())
	{
		delete _writerInputs[_writerInputs.size()-1];
		removeWriterInputPort();
	}
	while(nbWriterOutputs())
	{
		delete _writerOutputs[_writerOutputs.size()-1];
		removeWriterOutputPort();
	}

}


portIndex_t Node::addReaderInputPort()
{
//ScopedBlockMacro(scop_b,"addWriterOutputPort("+name+")");
//	portIndex_t index = getReaderInputCount();
	_readerInputs.push_back( new ReaderInputPort(this) );
	return _readerInputs.size()-1;
}

portIndex_t Node::addReaderOutputPort(Container* data)
{
//ScopedBlockMacro(scop_b,"addWriterOutputPort("+name+")");
//	portIndex_t index = getReaderOutputCount();
	_readerOutputs.push_back( new ReaderOutputPort(this, data) );
	return _readerOutputs.size()-1;
}

portIndex_t Node::addWriterInputPort()
{
//ScopedBlockMacro(scop_b,"addWriterOutputPort("+name+")");
//	portIndex_t index = getWriterInputCount();
	_writerInputs.push_back( new WriterInputPort(this) );
	return _writerInputs.size()-1;
}

portIndex_t Node::addWriterOutputPort(Container* data) // TODO data
{
//ScopedBlockMacro(scop_b,"addWriterOutputPort("+name+")");
//	portIndex_t index = getWriterOutputCount();
	_writerOutputs.push_back( new WriterOutputPort(this) );
	return _writerOutputs.size()-1;
}

void Node::addContainer(Container* data, bool addReader, bool addWriter)
{
		_containers.add(data);
		if(addReader) addReaderOutputPort(data);
		if(addWriter) addWriterOutputPort(data);
}



void 
Node::removeReaderInputPort()
{
	_readerInputs.pop_back();
}

void 
Node::removeReaderOutputPort()
{
	_readerOutputs.pop_back();
}

void 
Node::removeWriterInputPort()
{
	_writerInputs.pop_back();
}

void 
Node::removeWriterOutputPort()
{
	_readerOutputs.pop_back();
}

portIndex_t 
Node::indexOf(const ReaderInputPort& port) const
{
//ScopedBlockMacro(__scop, "Node::indexOf");
	for(unsigned i = 0; i < _readerInputs.size(); ++i)
		if(_readerInputs[i] == &port)
			return i;
			
	DEBUG_ONLY(
		Debug::error() 
			<< "Node::indexOf( ReaderInputPort& ) Error : unknown port !" 
			<< endl();
	)//DEBUG_ONLY
		
	//default value
	return 0;	
}

portIndex_t 
Node::indexOf(const WriterInputPort& port) const
{
//ScopedBlockMacro(__scop, "Node::indexOf");
	for(unsigned i = 0; i < _writerInputs.size(); ++i)
		if(_writerInputs[i] == &port)
			return i;
	DEBUG_ONLY(	
		Debug::error() 
			<< "Node::indexOf( WriterInputPort& ) Error : unknown port !" 
			<< endl(); 
	)//DEBUG_ONLY
	
	//default value
	return 0;
}

portIndex_t 
Node::indexOf(const ReaderOutputPort& port) const
{
//ScopedBlockMacro(__scop, "Node::indexOf");
	for(unsigned i = 0; i < _readerOutputs.size(); ++i)
		if(_readerOutputs[i] == &port)
			return i;
			
	DEBUG_ONLY(
		Debug::error() 
			<< "Node::indexOf( ReaderOutputPort& ) Error : unknown port !" 
			<< endl();
	)//DEBUG_ONLY
		
	//default value
	return 0;	
}

portIndex_t 
Node::indexOf(const WriterOutputPort& port) const
{
//ScopedBlockMacro(__scop, "Node::indexOf");
	for(unsigned i = 0; i < _writerOutputs.size(); ++i)
		if( _writerOutputs[i] == &port )
			return i;
			
	DEBUG_ONLY(
		Debug::error() 
			<< "Node::indexOf( WriterOutputPort& ) Error : unknown port !" 
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

// ---------------------------------------------------------- Port types


kiwi::Tags 
Node::readerInputTags(portIndex_t index) const
{
	return kiwi::Tags("#any");
}

kiwi::Tags 
Node::readerOutputTags(portIndex_t index) const
{
	return kiwi::Tags("#any");
}

kiwi::Tags 
Node::writerInputTags(portIndex_t index) const
{
	return kiwi::Tags("#any");
}

kiwi::Tags 
Node::writerOutputTags(portIndex_t index) const
{
	return kiwi::Tags("#any");
}

// -------------------------------------------------------- Port binding


void 
Node::bindPort(ReaderOutputPort& myPort, ReaderOutputPort& toBind)
{ 
	myPort.bind(toBind); 
}

void 
Node::bindPort(WriterOutputPort& myPort, WriterOutputPort& toBind)
{ 
	myPort.bind(toBind);
}

void 
Node::bindPort(ReaderInputPort& myPort, ReaderInputPort& toBind)
{ 
	myPort.bind(toBind); 
}

void 
Node::bindPort(WriterInputPort& myPort, WriterInputPort& toBind)
{ 
	myPort.bind(toBind); 
}


void
Node::setPortEnabled(ReaderInputPort& port, bool status)
{
	port.setEnabled(status);
}
void
Node::setPortEnabled(WriterInputPort& port, bool status)
{
	port.setEnabled(status);
}
void
Node::setPortEnabled(ReaderOutputPort& port, bool status)
{
	port.setEnabled(status);
}
void
Node::setPortEnabled(WriterOutputPort& port, bool status)
{
	port.setEnabled(status);
}


// ----------------------------------------------------------- Operators


bool 
operator >> (ReaderOutputPort& output, ReaderInputPort& input )
{
	if(!input.isConnected())
	{
		Debug::print() << "operator >> " << endl();
		return input.connect(output);
	}else{return false;}
}

bool 
operator >> (WriterOutputPort& output, WriterInputPort& input )
{
	if(!input.isConnected())
	{
		input.connect(output);
		return true;
	}else{return false;}
}




}//namespace core
}//namespace kiwi
