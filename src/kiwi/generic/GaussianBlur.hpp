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
 * @file GaussianBlur.hpp
 * @brief Header file for the generic gaussian blur filter
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.2
 */

#pragma once

#ifndef KIWI_GENERIC_GAUSSIANBLUR_HPP
#define KIWI_GENERIC_GAUSSIANBLUR_HPP

#include "kiwi/core/Filter.hpp"

namespace kiwi
{
namespace generic
{	

/**
 * @brief Generic gaussian blur Filter.
 * 
 * This Filter can be applied to any array based Container of dimension superior
 * to zero and with a scalar type that has basic arithmetic operators (+,-,/...).
 * 
 * <h2> Input ports </h1>
 * <h3> Reader </h3>
 * The first Reader input port corresponds to the blur strength:
 * <ul>
 *	<li> if a Value_uint32 is connected, the blur will be applied uniformly.</li>
 * 	<li> if an ArrayNd_uint8 is connected (with N equal to TDimension), this input
 * will be used as a mask that regulates the blur radius for each fragment.</li>
 * <br/>
 * The next K Reader input ports are the image inputs that we want to blur. They must
 * be of any type compatible with ArrayReader<TValueType, TDimension> (Container
 * class deriving from AbstractArrayContainer). The number K of these ports is not
 * limited.
 */ 
template<typename TValueType, unsigned TDimension>
class GaussianBlur<TValueType, TDimension>
{
public:
	/**
	 * @brief Constructor.
	 */ 
	GaussianBlur();
	
	/**
	 * @brief Process method.
	 * 
	 * Implements the algorithm.
	 */ 
	void process():
	
	/**
	 * @brief called when a port is connected/disconnected.
	 */ 
	void layoutChanged();
	
protected:
	uint8_t _nbInputImages;
};

} //namespace
} //namespace

#endif
