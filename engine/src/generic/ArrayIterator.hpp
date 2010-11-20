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
 * @file ArrayIterator.hpp
 * @brief Header file for ArrayContainer's iterators.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.1
 */

#pragma once

#ifndef KIWI_ARRAYITERATOR_HPP
#define KIWI_ARRAYITERATOR_HPP

#include "generic/GenericIterator.hpp"

namespace kiwi
{
namespace generic
{

/**
 * @class ArrayIterator
 * @brief Iterator class working with contiguous data containers.
 * 
 * This iterator class has been designed to work with ArrayContainer but
 * is compatible with any continuous data container.
 * The iterator needs to know the starting pointer and the pointer to 
 * the last value, as well as the increment value to iterate through
 * interleaved arrays.
 */ 
template<typename ValueTypeT>
class ArrayIterator : public GenericIterator<ValueTypeT>
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	typedef GenericIterator<ValueTypeT> Parent;

	/** 
	 * @brief Constructor. 
	 * 
	 * @param dataPtr A pointer to the first element.
	 * @param endPtr A pointer to the last element.
	 * @param increment The increment for each iteration.
	 * 
	 */ 
	ArrayIterator(ValueType* dataPtr
		, ValueType* endPtr
		, unsigned int increment=1 );
	// methods
	/**
	 * @brief Move forward.
	 * 
	 * For performances no bounding check is performed.
	 */ 
	bool operator ++ ();
	
	/**
	 * @brief Move backward.
	 * 
	 * For performances no bounding check is performed.
	 */ 
	bool operator -- ();
	
	/**
	 * @brief Determines wether or not the iterator has finished 
	 * iterating through the range.
	 * 
	 */ 
	bool isDone();
	
	/**
	 * @brief Move forward, returns false if not possible.
	 * 
	 * This method is designed to be used in a loop :
	 * | do {
	 * |	// use *it
	 * | while( it.onIteration() );
	 */ 
	bool onIteration();

protected:
	unsigned _increment;
	ValueType* _end;
};



/**
 * @class ArrayConstIterator
 * @brief const iterator class working with contiguous data containers.
 * 
 * This iterator class has been designed to work with ArrayContainer but
 * is compatible with any continuous data container.
 * The iterator needs to know the starting pointer and the pointer to 
 * the last value, as well as the increment value to iterate through
 * interleaved arrays.
 */ 
template<typename ValueTypeT>
class ArrayConstIterator : public GenericConstIterator<ValueTypeT>
{
public:
	// -------------------------------------------------------- typedefs
	typedef ValueTypeT ValueType;
	typedef GenericConstIterator<ValueTypeT> Parent;
	// ----------------------------------------------------- constructor

	/** 
	 * @brief Constructor. 
	 * 
	 * @param dataPtr A pointer to the first element.
	 * @param endPtr A pointer to the last element.
	 * @param increment The increment for each iteration.
	 */ 
	 ArrayConstIterator(ValueType* dataPtr
		, ValueType* endPtr
		, unsigned int increment=1 );
	// --------------------------------------------------------- methods
	/**
	 * @brief Move forward.
	 * 
	 * For performances no bounding check is performed.
	 */ 
	bool operator ++ ();
	
	/**
	 * @brief Move backward.
	 * 
	 * For performances no bounding check is performed.
	 */ 
	bool operator -- ();
	/**
	 * @brief Determines wether or not the iterator has finished 
	 * iterating through the range.
	 * 
	 */ 
	bool isDone();
	/**
	 * @brief Move forward, returns false if not possible.
	 * 
	 * This method is designed to be used in a loop :
	 * | do {
	 * |	// use *it
	 * | while( it.onIteration() );
	 */ 
	bool onIteration();
	
protected:
	
	unsigned _increment;
	ValueType* _end;
};


} // namsepace
} // namespace



#include "generic/ArrayIterator.ih"

#endif
