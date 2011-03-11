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



#ifndef KIWI_ABSTRACTTEXTCONTAINER_HPP
#define KIWI_ABSTRACTTEXTCONTAINER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/text/Line.hpp"
#include <iostream>


namespace kiwi{
namespace text{

	
class TextContainerInterface : public core::Container
{
public:
	typedef uint8_t lock_t;

	/** 
	 * @brief Returns A pointer to the requested line.
	 * 
	 * If the line number doesn't exists in the text, return a null
	 * pointer.
	 * The number of the first line is 0.
	 * 
	 * @param lineNumber The number of the requested line. 
	 */ 
	virtual kiwi::text::Line& line(kiwi::uint32_t lineNumber) = 0;
	virtual const kiwi::text::Line& line(kiwi::uint32_t lineNumber) const = 0;

	/**
	 * @brief Returns the number of lines in the container.
	 */ 
	virtual kiwi::uint32_t nbLines() const = 0;

	/**
	 * @brief Inserts a line.
	 * 
	 * @param toInsert The line to copy and insert in the container
	 * @param position The line will be insterted before the given position.
	 */ 
	virtual void insertLine(const Line& toCopy, kiwi::uint32_t position ) = 0;

	/**
	 * @brief Removes a line. 
	 */
	virtual void removeLine(kiwi::uint32_t position) = 0;
	virtual void removeLines(kiwi::uint32_t firstLine, kiwi::uint32_t lastLine) = 0;
	 /**
	  * @brief Clears the data.
	  */
	virtual void clear() = 0;
	  
	 /**
	  * @brief Clears the data.
	  */
	virtual void append(std::istream& stream) = 0;
/*
	virtual kiwi::uint32_t lock( kiwi::uint32_t firstLinePos
		, kiwi::uint32_t lastLinePos ) = 0;
	void unlock( lock_t );

	bool isLocked(kiwi::uint32_t firstLinePos, kiwi::uint32_t lastLinePos) const;
*/
	   
	 virtual ~TextContainerInterface() {}
};



}// namespace
}// namespace

#endif


// --
