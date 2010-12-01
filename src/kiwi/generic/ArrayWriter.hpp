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

#ifndef KIWI_ARRAYWRITER_HPP
#define KIWI_ARRAYWRITER_HPP

#include "core/Container.hpp"
#include "generic/AbstractArrayContainer.hpp"


/**
 * @file ArrayWriter.hpp
 * @brief Header file for the generic Writer of array based containers.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.1
 */

namespace kiwi
{
namespace generic
{
	
/**
 * @brief Writer class able to read and write data in any Container inheriting
 * from kiwi::generic::AbstractArrayContainer. 
 * 
 * 
 * (like kiwi::generic::ArrayContainer, kiwi::generic::MultiArrayContainer 
 * or kiwi::image::CairoImageContainer).
 * 
 */ 	
template < typename TValueType, unsigned int TDimension>
class ArrayWriter : public core::Writer
{
public:
	typedef TValueType ValueType;
	typedef ArrayIterator<TValueType> IteratorType;
	typedef Point<unsigned int, TDimension+1> IncsType;
	typedef Point<unsigned int, TDimension> Coordinates;
	
	// -----------------------------------------------------------------
	/**
	 * @brief Constructor.
	 */ 
	ArrayWriter(const core::Container::WriterInputPort& port);
	ArrayWriter(const AbstractArrayContainer<ValueType,TDimension>& resource, portIndex_t portIndex);
	
	/**
	 * @brief Basic access method.
	 */ 
	ValueType get(const Point<int, TDimension>& coords) const;	
	/**
	 * @brief Basic access method.
	 */ 
	ValueType get(unsigned int i) const;
	
	/**
	 * @brief Basic access method.
	 */ 
	void set(const Point<int, TDimension>& coords, ValueType value);
	/**
	 * @brief Basic access method.
	 */ 
	void set(unsigned int i, ValueType value);
	
	/**
	 * @brief span sizes.
	 */ 
	const Coordinates& spanSize() const { return _span; }
	
	/**
	 * @brief Returns the number of scalar objects in the Container.
	 */ 
	uint32_t nbScalarElements() const ;
	
	/**
	 * @brief Unsafe yet faster access method.
	 */ 
	inline const ValueType* getDataPointer() const { return _data; } 
	
	/**
	 * @brief Returns an iterator to the beguinning of the data.
	 */ 
	ArrayIterator<TValueType> getIterator() const ;
	
	/**
	 * @brief Returns an iterator that browses through a span
	 * 
	 * @param dim The dimension in which we want to iterate (x,y..)
	 * @param origin the first element pointed by the span iterator
	 */ 
	ArrayIterator<TValueType> getSpanIterator(
		const Point<uint32_t, TDimension>& origin
		, uint8_t dim  
		) const ;

	/**
	 * @brief Returns an iterator that browses through a span.
	 * 
	 * @param origin the first element pointed by the span iterator
	 * @param dim The dimension in which we want to iterate (x,y..)
	 */ 
	ArrayIterator<TValueType> getSpanIterator(
		const ArrayIterator<TValueType>& origin
		, uint8_t dim  
		) const ;
	
	Point<uint32_t,TDimension> positionOf(const ArrayIterator<TValueType>& it) const;
	
protected:
 ValueType* _data;
 ValueType* _end;
 IncsType _incs;
 portIndex_t _port;
 Coordinates _span;
};


}	
} // namespace


#include "generic/ArrayWriter.ih"


#endif
