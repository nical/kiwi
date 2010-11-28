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
 * @file CanonicalFilter.hpp
 * @brief Header file for the base class of Filter's Canonical form.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.1
 */


#pragma once

#ifndef KIWI_CANONICALFILTER_HPP
#define KIWI_CANONICALFILTER_HPP


#include "core/Filter.hpp"


namespace kiwi
{
namespace core
{	

class CanonicalFilter : public Filter
{
public:
	typedef Filter Parent;
	
	/**
	 * @brief Constructor.
	 * 
	 * Adds nbWriterInputs Writer input ports and Reader input ports. 
	 */ 
	CanonicalFilter(uint32_t nbWriterInputs);
	
	/**
	 * @brief Automatically publishes the Container's ports in this Filter's
	 * Reader output ports.
	 * 
	 * The child classes, if they override this method, *must* call their
	 * parent's method as the only feature that brings this class is in 
	 * here.
	 */ 
	void layoutChanged();
	
	

	
};



}// namespace
}// namespace


#endif
