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


#include "CanonicalFilter.hpp"


namespace kiwi
{
namespace core
{

CanonicalFilter::CanonicalFilter(uint32_t nbWriters)
: Filter()
{
ScopedBlockMacro(__scp, "CanonicalFilter::constructor")
	_wNodes = new Node*[nbWriters];
	_nbWNodes = nbWriters;
	for(uint32_t i = 0; i < nbWriters; ++i)
	{
		addWriterInputPort();
		addReaderOutputPort();
		setPortEnabled(readerOutputPort(i),false);
		_wNodes[i] = 0;
	}
}

CanonicalFilter::~CanonicalFilter()
{
	for(int i = 0; i < _nbWNodes; ++i )
		removeWriteNode(i);
}

void CanonicalFilter::layoutChanged()
{
	uint32_t nbWriters = nbWriterInputs();
	ScopedBlockMacro(__scop, "CanonicalFilter::layoutChanged")
	for(uint32_t i = 0; i < nbWriters; ++i)
	{
		if(writerInputPort(i).isConnected() )
		{
			if( !readerOutputPort(i).isEnabled() )
			{
				setPortEnabled(readerOutputPort(i),true);
				portIndex_t outIndex = writerInputPort(i).connectedOutput()->index();
				ReaderOutputPort& op
				= writerInputPort(i).connectedOutput()->node()->readerOutputPort(outIndex);
				bindPort( readerOutputPort(i), op );
			}
		}
		else
		{
			readerOutputPort(i).disconnect();
			setPortEnabled(readerOutputPort(i),false);	
		}
	}
}


void CanonicalFilter::addWriteNode(Node* toAdd, portIndex_t writerPort)
{
	if( _wNodes[writerPort] != 0) return;
	
	_wNodes[writerPort] = toAdd;
	_wNodes[writerPort]->writerOutputPort(0) >> writerInputPort(writerPort);
}

void CanonicalFilter::removeWriteNode(portIndex_t writerPort)
{
	if( _wNodes[writerPort] == 0 ) return;
	
	writerInputPort(writerPort).disconnect();
	delete _wNodes[writerPort];
	_wNodes[writerPort] = 0;
}



}// namespace	
}// namespace	
