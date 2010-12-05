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
 * @file InputWrapper.hpp
 * @brief Wraps the command-line inputs in a format that can be read by the filter to process.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva) 
 */

#pragma once

#ifndef KIWI_INPUTWRAPPER_HPP
#define KIWI_INPUTWRAPPER_HPP

#include "kiwi/core/NodeFactory.hpp"
#include "kiwi/text.hpp"
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "boost/filesystem.hpp"
#include "boost/lexical_cast.hpp"

namespace kiwi
{


void wrapInputs(core::NodeFactory& factory, core::Filter& filter, std::list<string>& inputs)
{
	typedef std::list<string> ArgList;
	ArgList::iterator it = inputs.begin();
	ArgList::iterator itEnd = inputs.end();
	int i=0;
	while(it != itEnd)
	{	
		
		if(boost::filesystem::exists( *it ) && !boost::filesystem::is_directory( *it ) ) 
		{	
			
			//std::cout << "input file exists" << std::endl;
			kiwi::text::TextContainer* inputText = new kiwi::text::TextContainer;

			std::ifstream file(it->c_str() );
			assert( file.is_open() );

			inputText->init(file);
			
			inputText->readerOutputPort(0) >> filter.readerInputPort(i);
			
		}else{
			//std::cout << "input is not a file" << std::endl;
			
			//Creation of a basic container, needed to apply the filter
			kiwi::text::TextContainer* basicInputContainer = new kiwi::text::TextContainer;
			
			 //Creation of a Writer needed to write the argument in the container
			kiwi::text::TextWriter writer(*basicInputContainer,0);
			
			writer.getLine() = inputs.front();
			std::cout << "debug: " << writer.getLine() << std::endl;
			//Connexion between the input container and the filter, then apply filter
			basicInputContainer->readerOutputPort(0) >> filter.readerInputPort(0);
			if(!filter.readerInputPort(0).isConnected() ) 
				std::cerr << "connection error"<<std::endl;

		}
		++i;
		++it;
	}
	
}


}//namespace

#endif
