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

/**
 * @file TextReader.hpp
 * @brief Reader for TextContainerInterface based containers.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva) 
 */

#pragma once

#ifndef KIWI_TEXTREADER_HPP
#define KIWI_TEXTREADER_HPP

#include "kiwi/text/TextContainerInterface.hpp"
#include "kiwi/text/PlainTextAccessor.hpp"
#include "kiwi/text/PlainTextLine.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/generic/ArrayIterator.hpp"
#include "kiwi/core/Node.hpp"

namespace kiwi{
namespace text{

typedef kiwi::generic::ArrayConstIterator<kiwi::int8_t> StringConstIterator;
	
class TextReader : public PlainTextAccessor
{
public:

	typedef kiwi::int8_t char_t;

	TextReader( TextContainerInterface& container, portIndex_t index
		, kiwi::uint32_t firstLine = 0
		, kiwi::uint32_t range = 0 );
	TextReader( core::ReaderPort& port
		, kiwi::uint32_t firstLine = 0
		, kiwi::uint32_t range = 0 ); 
	TextReader( core::DataPort& port
		, kiwi::uint32_t firstLine = 0
		, kiwi::uint32_t range = 0 ); 
	

	
	kiwi::uint32_t nbLines() const { return _nbLines; }
	
	const kiwi::text::Line& line(kiwi::int32_t lineNb) const;
	char_t getChar(int32_t charNumber) const;

	TextReader readerOnRange( kiwi::uint32_t firstLine, kiwi::uint32_t lastLine ){
		return TextReader(*_container, 0
				, _firstLine + firstLine
				, lastLine - firstLine + 1 );
	}

};	
	
}// namespace	
}// namespace	

#endif
