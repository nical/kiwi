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
#include <list>
#include <string>
#include "boost/filesystem.hpp"
#include "boost/lexical_cast.hpp"

namespace kiwi
{


void wrapInput(core::NodeFactory& factory, core::Filter& filter, std::list<string>& inputs)
{
	typedef std::list<string> ArgList;
	ArgList::iterator it = inputs.begin();
	ArgList::iterator itEnd = inputs.end();
	while(it != itEnd)
	{	
		if(boost::filesystem::exists( *it ) )
		{	
			std::cout << "input file exists" << std::endl;
		}else{
			std::cout << "input is not a file" << std::endl;
		}
		++it;
	}
	
}


}//namespace

#endif
