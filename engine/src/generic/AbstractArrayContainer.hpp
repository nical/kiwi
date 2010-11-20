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

#ifndef KIWI_ARRAYRESOURCE_HPP
#define KIWI_ARRAYRESOURCE_HPP

#include "core/Container.hpp"
#include "generic/Point.hpp"
//#include "generic/ArrayReader.hpp"
//#include "generic/ArrayWriter.hpp"

namespace kiwi
{
/**
 * @brief Namespace containing generic classes useful for a different kiwi
 * sub-projects.
 */ 	
namespace generic
{

template <typename TValueType, unsigned int TDimension> class ArrayReader;
template <typename TValueType, unsigned int TDimension> class ArrayWriter;

/**
 * @brief Interface class for containers based on an array structure.
 */ 
template <typename TValueType, unsigned int TDimension>
class AbstractArrayContainer : public core::Container
{
public:
	typedef TValueType ValueType;
	typedef ArrayReader<TValueType, TDimension> ReaderType;
	typedef ArrayWriter<TValueType, TDimension> WriterType;
	// -----------------------------------------------------------------------
	/**
	 * Returns a pointer to the first element associated to a given port.
	 */ 
	virtual ValueType* const getDataPointer(portIndex_t index) const = 0 ;
	/**
	 * Returns the increments or stride.
	 */ 
	virtual Point<unsigned int, TDimension+1> increments(portIndex_t index) const = 0;
	/**
	 * Returns the size of each span.
	 */ 
	virtual Point<unsigned int, TDimension> spanSize() const = 0;
		
	
	kiwi::string
	readerOutputType(portIndex_t)
	{
	return kiwi::string("array"
				+ boost::lexical_cast<kiwi::string>(TDimension)+"d_"
				+ types::str<TValueType>() );
	}


	kiwi::string
	writerOutputType(portIndex_t)
	{
	return kiwi::string("array"
				+ boost::lexical_cast<kiwi::string>(TDimension)+"d_"
				+ types::str<TValueType>() );
	}

};



} // neamspace
} // neamspace

#endif
