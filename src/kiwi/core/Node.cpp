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



Node::~Node()
{
	
}



kiwi::string Node::strCommand( const kiwi::string& command )
{
	return kiwi::string("kiwi::unknown_command");
}

// ---------------------------------------------------------- Port tags


kiwi::utils::Tags 
Node::readerTags(portIndex_t index) const
{
	return kiwi::utils::Tags("#any");
}

kiwi::utils::Tags 
Node::writerTags(portIndex_t index) const
{
	return kiwi::utils::Tags("#any");
}


kiwi::utils::Tags 
Node::dataTags(portIndex_t index) const
{
	return kiwi::utils::Tags("#any");
}



portIndex_t Node::indexOf(const ReaderPort& port) const {
//ScopedBlockMacro( "DynamicNode::indexOf");
	for(unsigned i = 0; i < nbReaderPorts(); ++i)
		if( &readerPort(i) == &port)
			return i;
			
	DEBUG_ONLY(
		Debug::error() 
			<< "DynamicNode::indexOf( ReaderPort& ) Error : unknown port !" 
			<< endl();
	)//DEBUG_ONLY
		
	//default value
	return 0;	
}

portIndex_t Node::indexOf(const WriterPort& port) const {
//ScopedBlockMacro( "DynamicNode::indexOf");
	for(unsigned i = 0; i < nbWriterPorts(); ++i)
		if( &writerPort(i) == &port )
			return i;
	DEBUG_ONLY(	
		Debug::error() 
			<< "DynamicNode::indexOf( WriterPort& ) Error : unknown port !" 
			<< endl(); 
	)//DEBUG_ONLY
	
	//default value
	return 0;
}


portIndex_t Node::indexOf(const DataPort& port) const {
//ScopedBlockMacro( "DynamicNode::indexOf");
	for(unsigned i = 0; i < nbDataPorts(); ++i)
		if( &dataPort(i) == &port )
			return i;
			
	DEBUG_ONLY(
		Debug::error() 
			<< "DynamicNode::indexOf( DataPort& ) Error : unknown port !" 
			<< endl();
	)//DEBUG_ONLY
		
	//default value
	return 0;	
}


// -------------------------------------------------------- Port binding


void Node::bindPort(DataPort& myPort, DataPort& toBind)
{ 
	myPort.bind(toBind);
}

void Node::bindPort(ReaderPort& myPort, ReaderPort& toBind)
{ 
	myPort.bind(toBind); 
}

void Node::bindPort(WriterPort& myPort, WriterPort& toBind)
{ 
	myPort.bind(toBind); 
}


void Node::setDataPortContainer(DataPort& port, Container* container)
{
	port.setContainer( container );
}



// ----------------------------------------------------------- Operators


bool 
operator >> (DataPort& output, ReaderPort& input )
{
	ScopedBlockMacro("operator >> (reader)" )
	if(!input.isConnected())
	{
		return input.connect(&output);
	}else{return false;}
}

bool 
operator >> (DataPort& output, WriterPort& input )
{
	ScopedBlockMacro( "operator >> (writer)" )
	if(!input.isConnected())
	{
		return input.connect(&output);
	}else{return false;}
}




}//namespace core
}//namespace kiwi
