#pragma once

#ifndef DEBUGOUTPUTSTREAM_HPP
#define DEBUGOUTPUTSTREAM_HPP

#include <iostream>
#include "Commons.hpp"

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

namespace kiwi
{


class DebugOutputStream
{
public:
	DebugOutputStream() {}
	~DebugOutputStream() {std::cerr << postfixReset();}
	inline void beginBlock(const string& message = "");
	inline void endBlock(const string& message = "");
//	inline void operator << (const string& text);
	inline std::ostream& error();
	inline std::ostream& print();
	inline std::ostream& emphase();
	inline void endl(char n = 1);
	//inline ScopedBlock scopedBlock(const string& message = "");
protected:
	std::string  prefixInfo();
	std::string  prefixError();
	std::string  prefixWarning();
	std::string  prefixEmphase();
	std::string  postfixReset();
	string indent();
	unsigned _indentation;
};

DebugOutputStream debug;



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


// ---------------------------------------------------------------------


class ScopedBlock
{
public:
	ScopedBlock( string message)
	: _message(message)
	{
		debug.beginBlock(_message);
	}
	~ScopedBlock()
	{
		debug.endBlock(_message);
	}
protected:
	string _message;
};



} //namespace

//#include "DebugOutputStream.ih"

#endif
