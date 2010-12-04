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


#include "TextContainer.hpp"


namespace kiwi
{
namespace text
{	

TextContainer::TextContainer()
	: _nbLines(1)
{
ScopedBlockMacro(__scop, "TextContainer::constructor")	
	_first = new Line;
	_last = _first;
	
	_first->_next = 0;
	_first->_prev = 0;
	_first->_text = kiwi::string("");
	
	addReaderOutputPort();
	addWriterOutputPort();
}

kiwi::string* TextContainer::getLine( kiwi::uint32_t lineNumber )
{
ScopedBlockMacro(__scop, "TextContainer::getLine")	
	// returns 0 if the line doesn't exist.
	if(lineNumber >= _nbLines ) 
	{
		DEBUG_ONLY( Debug::print() << "lineNumber >= _nbLines"<<endl(); )
		return 0;
	}
	
	Line* it = line(lineNumber);
	
	// TODO: It could be interesting to implement a faster access method 
	// using a hash table maybe...
	return &(it->_text);
}



void TextContainer::insertLine(
	const kiwi::string& toInsert
	, kiwi::uint32_t position )
{
ScopedBlockMacro(__scop, "TextContainer::insertLine")
	Debug::print() << "nbLines:" << _nbLines
			<< " pos: " << position << endl();
	if( position > _nbLines ) 
	{
		Debug::error() << "TextContainer::insertLine error: line" 
			<< position << "out of the container (" << _nbLines 
			<< "lines)."  << endl();
		return;
	}
	if( position == _nbLines ) // last line
	{
		Debug::print() << "inserting at the end" << endl();
		Line* temp = _last;
		_last = new Line;
		_last->_next = 0;
		_last->_prev = temp;
		temp->_next = _last;
		_last->_text = toInsert;
		++_nbLines;
		return;
	}
	if( position == 0 ) // first line
	{
		Debug::print() << "inserting at the beginning" << endl();
		Line* temp = _first;
		_first = new Line;
		_first->_prev = 0;
		_first->_next = temp;
		_first->_text = toInsert;
		++_nbLines;
		return;
	}
	Debug::print() << "inserting in the middle" << endl();
	// general case
	Line* thenext = line(position);
	Line* newline = new Line;
	newline->_text = toInsert;
	newline->_next = thenext;
	newline->_prev = thenext->_prev;
	// update neighbor lines
	thenext->_prev = newline;
	newline->_prev->_next = newline;
	++_nbLines;
	
}

void TextContainer::removeLine( kiwi::uint32_t position )
{
	if(_nbLines == 1) return;
	if(position >= _nbLines ) return ;
	if(position == 0)
	{
		_first->_next->_prev = 0;
		Line* temp = _first;
		_first = _first->_next;
		delete temp;
		--_nbLines;
		return;
	}
	else if(position == _nbLines-1) 
	{
		_last->_prev->_next = 0;
		Line* temp = _last;
		_last = _last->_prev;
		delete temp;
		--_nbLines;
		return;
	}
	else
	{
		Line* it = line(position);
		it->_prev->_next = it->_next;
		it->_next->_prev = it->_prev;
		delete it;
		--_nbLines;
	}
}

//-------------------------------------------------------------- private
TextContainer::Line* TextContainer::line(kiwi::uint32_t position)
{
ScopedBlockMacro(__scop, kiwi::string("TextContainer::line") )
	//Debug::print() << position << endl();
	Line* it = _first;
	for(kiwi::uint32_t i = 0; i < position; ++i)
	{
	//	Debug::print() << "haha " << i << endl();
		it = it->_next;
	}
	return it;
}

}// namespace
}// namespace
