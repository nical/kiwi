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


#ifndef KIWI_TEXTCONTAINER_HPP
#define KIWI_TEXTCONTAINER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/text/AbstractTextContainer.hpp"


namespace kiwi
{
namespace text	
{

class TextReader;
class TextWriter;
		
class TextContainer : public AbstractTextContainer
{
public:
	typedef TextReader ReaderType;
	typedef TextWriter WriterType;

	/**
	 * @brief Constructor. 
	 */ 
	TextContainer();

	/** 
	 * @brief Returns A pointer to the requested line.
	 * 
	 * If the line number doesn't exists in the text, return a null
	 * pointer.
	 * The number of the first line is 0.
	 * 
	 * @param lineNumber The number of the requested line. 
	 */ 
	virtual kiwi::string* getLine(kiwi::uint32_t lineNumber);
	
	
	/**
	 * @brief Returns the number of lines in the container.
	 */ 
	kiwi::uint32_t nbLines() const { return _nbLines; }
	
	
	/**
	 * @brief Inserts a line.
	 * 
	 * @param toInsert The line to copy and insert in the container
	 * @param position The line will be insterted before the position.
	 */ 
	void insertLine(const kiwi::string& toInsert, kiwi::uint32_t position);
	
	
	/**
	 * @brief Removes a line. 
	 */
	void removeLine(kiwi::uint32_t position);
	
private:

	/**
	 * @brief element of double linked list of lines.
	 */ 
	struct Line
	{
		Line* _next;
		Line* _prev;
		kiwi::string _text;
	};
	/**
	 * @brief Returns the position's line.
	 */ 
	Line* line(kiwi::uint32_t position);
	
	uint32_t _nbLines;
	Line* _first;
	Line* _last;
	
};



}// namespace
}// namespace

#endif


// --
