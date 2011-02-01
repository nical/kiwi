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
#include "kiwi/core/Tags.hpp"
#include "kiwi/text/AbstractTextContainer.hpp"
#include "kiwi/text/PlainTextLine.hpp"

namespace kiwi{
namespace text{

class TextReader;
class TextWriter;

class PlainTextContainer : public AbstractTextContainer
{
public:
	typedef TextReader ReaderType;
	typedef TextWriter WriterType;

	typedef kiwi::uint32_t lock_t;

	/**
	 * @brief Constructor.
	 */
	PlainTextContainer();

	void init(std::istream& inputStream);

	void append(std::istream& inputStream);

	void clear();

	bool hasSubData() const {return false;}
	kiwi::uint32_t memoryEstimation() const {return 0;}//TODO
	kiwi::uint32_t size() const {return 0;}//TODO



	/**
	 * @brief Returns A pointer to the requested line.
	 *
	 * If the line number doesn't exists in the text, return a null
	 * pointer.
	 * The number of the first line is 0.
	 *
	 * @param lineNumber The number of the requested line.
	 */
	Line* line(kiwi::uint32_t linePos);


	/**
	 * @brief Returns the number of lines in the container.
	 */
	kiwi::uint32_t nbLines() const { return _lines.size(); }


	/**
	 * @brief Inserts a line.
	 *
	 * @param toInsert The line to copy and insert in the container
	 * @param position The line will be insterted before the given position.
	 */
	void insertLine( const PlainTextLine& toInsert, kiwi::uint32_t position);
	void insertLine( const Line& toCopy, kiwi::uint32_t position);

	/**
	 * @brief Removes a line.
	 */
	void removeLine(kiwi::uint32_t position);
	void removeLines(kiwi::uint32_t firstLine, kiwi::uint32_t lastLine);

// ---------------------------------------------------------------------
// threading tools

	lock_t lock(kiwi::uint32_t firstLinePos
		, kiwi::uint32_t lastLinePos );

	void unlock( lock_t );

	bool isLocked(kiwi::uint32_t firstLinePos, kiwi::uint32_t lastLinePos) const;

// ---------------------------------------------------------------------
// tags

	kiwi::Tags tags() const
	{
			return kiwi::Tags("#text#rawText");
	}
	kiwi::Tags outputReaderTags(portIndex_t)
	{
			return kiwi::Tags("#text#rawText");
	}
	kiwi::Tags outputWriterTags(portIndex_t)
	{
			return kiwi::Tags("#text#rawText");
	}

// ---------------------------------------------------------------------
// attributes

protected:

	std::list<kiwi::text::PlainTextLine> _lines;

};



}// namespace
}// namespace

#endif


// --
