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


#include "TextReader.hpp"
#include "kiwi/utils/modulo.hpp"


namespace kiwi{
namespace text{


TextReader::TextReader( AbstractTextContainer& container 
	, portIndex_t index
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range )
{
ScopedBlockMacro(__scop, "TextReader::constructor")
	init(container, index, firstLine, range);
}

TextReader::TextReader( core::Node::ReaderInputPort& port
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range )
{
ScopedBlockMacro(__scop, "TextReader::constructor")
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


TextReader::TextReader( core::Node::ReaderOutputPort& port
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range )
{
ScopedBlockMacro(__scop, "TextReader::constructor")
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


void TextReader::init( AbstractTextContainer& container
	, portIndex_t portIndex
	, kiwi::uint32_t firstLine
	, kiwi::uint32_t range  )
{
	_container = &container;
	_firstLine = firstLine;
	if( range == 0 ){
		_containerRange = _container->nbLines() - firstLine;
	}else if( range > _container->nbLines() - firstLine ){
		_containerRange = _container->nbLines() - firstLine;
	}else{
		_containerRange = range;
	}

	Debug::print() << "TextReader::init \n first line = " << _firstLine
		<< "\n range = " << _containerRange << endl();
}

const kiwi::text::Line& TextReader::line(kiwi::int32_t lineNb) const
{
//	Debug::print() << "TextReader::line(" << lineNb << ")\n";
	if( _containerRange == 0 ) return RawTextLine( "" );
	if( lineNb >= _containerRange ) lineNb = _containerRange-1;
	//if( lineNb <= -_containerRange ) lineNb = 0;
	if( lineNb < 0 ) lineNb = _containerRange + lineNb; 

	return *(_container->line( _firstLine + lineNb ) );
	
}

kiwi::uint32_t TextReader::nbChars() const
{
	kiwi::uint32_t result = 0;
	for(int i = 0; i < _containerRange; ++i){
		result += _container->line(_containerRange+i)->size();
	}
	return result;
}


}// namespace	
}// namespace	


