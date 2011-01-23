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
 * @file TextWriter.hpp
 * @brief Writer for AbstractTextContainer based containers.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva) 
 */

#pragma once

#ifndef KIWI_TEXTWRITER_HPP
#define KIWI_TEXTWRITER_HPP

#include "kiwi/text/AbstractTextContainer.hpp"
#include "kiwi/text/PlainTextAccessor.hpp"

#include "kiwi/text/PlainTextLine.hpp"
#include <iostream>


namespace kiwi{
namespace text{

/**
 * @brief Writer class that can access Plain text Containers
 */ 
class TextWriter : public PlainTextAccessor
{
public:
	typedef kiwi::int8_t char_t;

	/**
	 * @brief Constructor.
	 */ 
	TextWriter(AbstractTextContainer& container
		, portIndex_t
		, kiwi::uint32_t firstLine = 0
		, kiwi::uint32_t range = 0 );
	/**
	 * @brief Constructor.
	 */
	TextWriter( core::WriterInputPort& port
		, kiwi::uint32_t firstLine = 0
		, kiwi::uint32_t range = 0 );
	/**
	 * @brief Constructor.
	 */
	TextWriter( core::WriterOutputPort& port
		, kiwi::uint32_t firstLine = 0
	 	, kiwi::uint32_t range = 0 );
	
	/**
	 * @brief Returns the number of lines.
	 */ 
	kiwi::uint32_t nbLines() const { return _nbLines; }

	/**
	 * @brief 
	 */ 
	kiwi::text::Line& line(kiwi::int32_t lineNb);

	/**
	 * @brief Returns a writer to a subset of this writer's data.
	 */ 
	TextWriter writerOnRange( kiwi::uint32_t firstLine, kiwi::uint32_t lastLine ){
		return TextWriter(*_container, 0
				, _firstLine + firstLine
				, lastLine - firstLine + 1 );
	}
	
	void insertLine(const kiwi::text::PlainTextLine& lineCopy
		, kiwi::int32_t position = -1);

	/**
	 * @brief Removes a line from the container.
	 *
	 * If the position passed in parameter is -1, the last line will be
	 * removed, if -2 the line before, etc...
	 * If position is greater than the number of lines accessible by the
	 * writer, nothing will be removed.  
	 */ 
	void removeLine(kiwi::int32_t position);

	/**
	 * @brief removes all the line accessible by the writer.
	 */ 
	void clear();

	/**
	 * @brief Inserts text from a stream into the container. 
	 */ 
	void insertStream(std::istream& inputStream
		, kiwi::int32_t position = -1)
	{
		// TODO insert at the given position and get the number of lines
		// added
		_container->append(inputStream);
		//_addedLines += ...
	}

private:
	kiwi::int32_t _addedLines; // to keep track of how many line have been
	//added and removed

};


}// namespace	
}// namespace	

#endif
