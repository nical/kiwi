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

#pragma once

#ifndef DEBUGOUTPUTSTREAM_HPP
#define DEBUGOUTPUTSTREAM_HPP

#include <iostream>
#include "core/Commons.hpp"

#define DEBUG

#define INDENTATION_PATTERN 3
#define BEGIN_BLOCK_MESSAGE " Begin block "
#define END_BLOCK_MESSAGE " End block "


#ifdef DEBUG
#define ScopedBlockMacro(vname, message) kiwi::ScopedBlock vname(message);
#else
#define ScopedBlockMacro(vname, message) 
#endif


#ifdef DEBUG
#define __( instruction ) instruction
#else
#define __( instruction ) 
#endif

#ifdef DEBUG
#define DEBUG_ONLY( instruction ) instruction
#else
#define DEBUG_ONLY( instruction ) 
#endif

namespace kiwi
{


class DebugOutputStream
{
public:
	DebugOutputStream() {}
	~DebugOutputStream() {std::cerr << postfixReset();}
	static void beginBlock(const kiwi::string& message = "");
	static void endBlock(const kiwi::string& message = "");
//	inline void operator << (const string& text);
	static std::ostream& error();
	static std::ostream& print();
	static std::ostream& emphase();
	static void endl(char n = 1);
	//inline ScopedBlock scopedBlock(const string& message = "");
protected:
	static std::string  prefixInfo();
	static std::string  prefixError();
	static std::string  prefixWarning();
	static std::string  prefixEmphase();
	static std::string  postfixReset();
	static string indent();
	static unsigned _indentation;
};
typedef DebugOutputStream Debug;

// Debug::print() << " text" << endl();
// Debug::println( << "text" )

//DebugOutputStream debug;


class ScopedBlock
{
public:
	ScopedBlock(kiwi::string message)
	: _message(message)
	{
		Debug::beginBlock(_message);
	}
	~ScopedBlock()
	{
		Debug::endBlock(_message);
	}
protected:
	kiwi::string _message;
};




// ---------------------------------------------------------------------

string endl() 
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m\n";
#else
	return "\n";
#endif
}

// ---------------------------------------------------------------------

string DebugOutputStream::indent()
{
	return string(_indentation*INDENTATION_PATTERN, ' ');
}

void DebugOutputStream::beginBlock(const string& message)
{
#ifdef DEBUG
 std::cerr << prefixEmphase() <<indent() << "[" << BEGIN_BLOCK_MESSAGE << "] " << message<< postfixReset()<< std::endl;
_indentation ++;
#endif
}

void DebugOutputStream::endBlock(const string& message)
{
#ifdef DEBUG
	_indentation --;
	 std::cerr << prefixEmphase() << indent() << "[" << END_BLOCK_MESSAGE <<"] "<<message<< postfixReset() << std::endl;

#endif
}
/*
ScopedBlock DebugOutputStream::scopedBlock(const string& message)
{
	return ScopedBlock(this, message);
}
*/
std::ostream& DebugOutputStream::error()
{
	return std::cerr << prefixError() << indent() ;
}
std::ostream& DebugOutputStream::emphase()
{
	 return std::cerr << prefixEmphase() << indent() ;
}

std::ostream& DebugOutputStream::print()
{
	 std::cerr << indent();
	 return std::cerr;
}

void DebugOutputStream::endl(char n)
{
	for(; n > 0; --n) print() << kiwi::endl();
}

// ------------------------------- prefixes

std::string DebugOutputStream::prefixWarning() 
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m\033[35m";
#else
	return "";
#endif
}

std::string DebugOutputStream::prefixInfo()  
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m";
#else
	return "";
#endif
}

std::string DebugOutputStream::prefixError() 
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m\033[31m";
	//return "\033[0m\033[31m[ERR]";
#else
	return "";
#endif
}

std::string DebugOutputStream::prefixEmphase() 
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m\033[1m";
#else
	return "";
#endif
}

std::string DebugOutputStream::postfixReset() 
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m";
#else
	return "";
#endif
}



} //namespace

//#include "DebugOutputStream.ih"

#endif
