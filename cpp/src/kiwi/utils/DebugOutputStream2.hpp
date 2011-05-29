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

#ifndef KIWI_DEBUGOUTPUTSTREAM__HPP
#define KIWI_DEBUGOUTPUTSTREAM__HPP

#include <iostream>
#include "kiwi/core/Commons.hpp"

#define DEBUG


namespace kiwi{

	
class OutputStream
{
protected:

public:
	OutputStream(std ostream& stream) { _stream = *stream; }
	~OutputStream() { *_stream << utils::terminal::postfixReset();}

	void operator++(){
		++_indentation;
	}
	void operator--(){
		--_indentation;
	}

	void setIndentation( int32_t nb ){
		_indentation = nb;
	}

	void resetEnvironment(){
		_environment.clear();
	}

	void enter( const kiwi::string& environment ){
		_environment.insert( environment );
	}
	
	void leave( const kiwi::string& environment ){
		_environment.erase( environment );
	}
	
	
	void beginBlock(const kiwi::string& message = "")
	{
			*_stream << utils::terminal::prefixEmphase() << indent();
			
			if(_showBeginBlock){
				*_stream << "[" << BEGIN_BLOCK_MESSAGE << "] ";
					*_stream << message
					<< utils::terminal::postfixReset()
					<< std::endl;
			}
			_indentation ++;
	}
	
	void endBlock(const kiwi::string& message = "")
	{
		_indentation --;
		if( _showEndBlock )
		{
			*_stream << prefixEmphase() << indent()
				<< "[" << END_BLOCK_MESSAGE <<"] "
				<< message << postfixReset() << std::endl;
		}
	}

	static std::ostream& error()
		{ return *_stream << prefixError() << indent() ; }
		
	static std::ostream& print()
	{
		*_stream << indent();
		return *_stream;
	}
	
	static std::ostream& bold()
	{
		return *_stream << prefixEmphase() << indent() ;
	}
	
	static void newLine(char n = 1)
	{
		for(; n > 0; --n) print() << "\n" //todo!
	}

protected:
	int _indentation;
	std::ostream* _stream;
	std::set< kiwi::string > _environment;

} //namespace

/* use cases

Debug.enableEnvironment( "test" );

Debug.setStream( cout );
Debug.addEnvironment( "test" );

++Debug // indent
Debug.indent( int nb )

Debug.print( "iteration " <<  i  << "\n");
 
*/

#endif
