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
 * @file ArrayReader.hpp
 * @brief Header file for the generic Reader of array based containers.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.1
 */


#pragma once

#ifndef KIWI_ARRAYDATAREADER_HPP
#define KIWI_ARRAYDATAREADER_HPP

#include "kiwi/core/Container.hpp"
#include "kiwi/generic/ArrayContainerInterface.hpp"
#include "kiwi/generic/ArrayIterator.hpp"


namespace kiwi
{
namespace generic
{

/**
 * @brief Reader class able to read data from any Container inheriting
 * from kiwi::generic::AbstractArrayContainer.
 *
 * (like kiwi::generic::ArrayContainer, kiwi::generic::MultiArrayContainer
 * or kiwi::image::CairoImageContainer).
 *
 */
template < typename TValueType, unsigned int TDimension>
class ArrayReader : public core::Reader
{
public:
	typedef TValueType ValueType;
	typedef ArrayConstIterator<TValueType> IteratorType;
	typedef Point<unsigned int, TDimension+1> IncsType;
	typedef Point<unsigned int, TDimension> Coordinates;


	// -----------------------------------------------------------------
	/**
	 * @brief Constructor.
	 */
	ArrayReader(const core::ReaderInputPort& port);
	ArrayReader(const AbstractArrayContainer<ValueType,TDimension>& resource, portIndex_t portIndex);

	/**
	 * @brief Basic access method.
	 */
	ValueType get(const Point<int, TDimension>& coords) const;

	/**
	 * @brief Basic access method.
	 */
	ValueType get(unsigned int i) const;

	/**
	 * @brief span sizes.
	 */
	const Coordinates& spanSize() const { return _span; }

	/**
	 * @brief returns the total amount of data
	 */
	uint32_t nbScalarElements() const ;

	/**
	 * @brief Unsafe yet faster access method.
	 */
	inline const ValueType* getDataPointer() const { return _data; } 	// TODO: const stuff

	/**
	 * @brief Returns an iterator to the beguinning of the data.
	 */
	ArrayConstIterator<TValueType> getIterator() const ;

	/**
	 * @brief Returns an iterator that browses through a span
	 *
	 * @param dim The dimension in which we want to iterate (x,y..)
	 * @param origin the first element pointed by the span iterator
	 */
	ArrayConstIterator<TValueType> getSpanIterator(
		const Point<uint32_t, TDimension>& origin
		, uint8_t dim
		) const ;

	/**
	 * @brief Returns an iterator that browses through a span
	 *
	 * @param origin the first element pointed by the span iterator
	 * @param dim The dimension in which we want to iterate (x,y..)
	 */
	ArrayConstIterator<TValueType> getSpanIterator(
		const ArrayConstIterator<TValueType>& origin
		, uint8_t dim
		) const ;

	Point<uint32_t, TDimension> positionOf(const ArrayConstIterator<TValueType>&);

protected:
 ValueType* _data;
 IncsType _incs;
 Coordinates _span;
 portIndex_t _port;
};



}
} // namespace


#include "kiwi/generic/ArrayReader.ih"


#endif
