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


namespace kiwi
{
namespace text	
{


TextReader::TextReader( const AbstractTextContainer& container )
{
	
}

TextReader::TextReader( core::Node::ReaderInputPort& port )
{
	
}

kiwi::uint32_t TextReader::nbLines() const
{
	return _container->nbLines();
}

kiwi::uint32_t TextReader::nbChars() const
{
	return _currentLine->size();
}

kiwi::uint32_t TextReader::currentLine() const
{
	return _currentLineNb;
}

bool TextReader::gotoLine(kiwi::int32_t lineNumber)
{
	// TODO: modulo opération 
	// this is really unsafe, i mean really !
	_currentLine = _container->getLine(lineNumber);
	if(_currentLine ) _currentLineNb = lineNumber;
}

bool TextReader::gotoNextLine()
{
	gotoLine(_currentLineNb + 1);
}

bool TextReader::gotoPreviousLine()
{
	gotoLine(_currentLineNb - 1);
}

bool TextReader::endOfText() const
{
	return (_currentLineNb >= _container->nbLines() );
}

kiwi::string TextReader::getLine() const
{
	return *_currentLine;
}

kiwi::uint8_t TextReader::getChar(int32_t charNumber) const
{
	return (*_currentLine)[charNumber];
}

StringConstIterator TextReader::getStringIterator() const
{
/*	return StringConstIterator( 
		&((*_currentLine)[0])
		, &(*_currentLine[_currentLine->size()-1]) );
*/
}


	
}// namespace	
}// namespace	


