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


#include "RawTextContainer.hpp"


namespace kiwi{
namespace text{	

RawTextContainer::RawTextContainer()
{
	// noting to do
}

Line* RawTextContainer::line(kiwi::uint32_t linePos)
{
	// out of bounds...
	if(linePos > nbLines() ) return 0;
	
	//general case
	std::list<kiwi::text::RawLine>::iterator it = _lines.begin();
	while( linePos > 0 ){
		++it;
		--linePos;
	}
	return &(*it);
}

void RawTextContainer::reset()
{
	_lines.clear();
}

void RawTextContainer::append(std::istream& inputStream)
{
	while( !inputStream.eof() )
	{
		kiwi::string line;
		std::getline(inputStream, line);
		insertLine(RawLine(line), nbLines() );
	}
}

void RawTextContainer::init(std::istream& inputStream)
{
	reset();
	append(inputStream);
}

RawTextContainer::lock_t RawTextContainer::lock(kiwi::uint32_t firstLinePos
		, kiwi::uint32_t lastLinePos )
{

}			

void RawTextContainer::unlock( RawTextContainer::lock_t id )
{
	
}

bool RawTextContainer::isLocked(kiwi::uint32_t firstLinePos, kiwi::uint32_t lastLinePos)
{

}


}// namespace
}// namespace
