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


#include "TextWriter.hpp"
#include "kiwi/utils/modulo.hpp"

namespace kiwi{
namespace text{




TextWriter::TextWriter( AbstractTextContainer& container 
	, portIndex_t index
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range )
{
ScopedBlockMacro(__scop, "TextWriter::constructor")
	init(container, index, firstLine, range);
}

TextWriter::TextWriter( core::Node::WriterInputPort& port
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range )
{
ScopedBlockMacro(__scop, "TextWriter::constructor")
	AbstractTextContainer* tc = dynamic_cast<AbstractTextContainer*>(
		port.connectedOutput()->subPort()->node() );
	
	if( tc ) init( *tc, port.connectedOutput()->subPort()->index()
		, firstLine, range );
	else
	{
		Debug::error() 
			<< "TextReader::constructor error:"
			<<" Unable to determine the Container type."
			<< endl();
	}
}

TextWriter::TextWriter( core::Node::WriterOutputPort& port
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range )
{
ScopedBlockMacro(__scop, "TextWriter::constructor")
	AbstractTextContainer* tc = dynamic_cast<AbstractTextContainer*>(
		port.subPort()->node() );
	
	if( tc ) init( *tc, port.subPort()->index(), firstLine, range );
	else
	{
		Debug::error() 
			<< "TextReader::constructor error:"
			<<" Unable to determine the Container type."
			<< endl();
	}
}



kiwi::text::Line& TextWriter::line(kiwi::int32_t lineNb)
{
	// todo: here we have a problem if the Writer's range is 0 
	return *(_container->line( _firstLine + position(lineNb) ) );	
}

void TextWriter::insertLine( const kiwi::text::PlainTextLine& lineCopy
	, kiwi::int32_t pos )
{
	_container->insertLine( lineCopy, _firstLine + position( pos ) );
}


void TextWriter::clear() 
{
	_container->removeLines(_firstLine, _firstLine + _containerRange);
	_containerRange = 0;
}

	
}// namespace	
}// namespace	
