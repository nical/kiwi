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
 * @file ArrayContainer.hpp
 * @brief Header file for an array based Container.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.3
 */


#pragma once

#ifndef KIWI_ARRAYDATA_HPP
#define KIWI_ARRAYDATA_HPP

#include "kiwi/generic/ArrayContainerInterface.hpp"
#include "kiwi/generic/ArrayReader.hpp"
#include "kiwi/generic/ArrayWriter.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/utils/types.hpp"
#include "kiwi/generic/ArrayIterator.hpp"
#include "kiwi/core/NodeFactory.hpp"

#include <boost/lexical_cast.hpp>

namespace kiwi{
namespace generic{


/**
 * @brief Templated container class based on contiguous array buffers.
 *
 */
template<typename TValueType, unsigned int TDimension>
class ArrayContainer : public ArrayContainerInterface<TValueType, TDimension>
{
public:
	typedef TValueType ValueType;
	typedef ArrayReader<TValueType, TDimension> ReaderType;
	typedef ArrayWriter<TValueType, TDimension> WriterType;
	typedef ArrayConstIterator<TValueType> ConstIteratorType;
	typedef ArrayIterator<TValueType> IteratorType;

	/**
	 * @brief The Point type used to adress a value in this container.
	 */
	typedef Point<unsigned int, TDimension> CoordinateVector;

	/**
	 * @brief The Point type used to contain the increments of this
	 * container.
	 */
	typedef Point<unsigned int, TDimension> StrideVector;


	/**
	 * @brief Constructor (allocates the data).
	 */
	ArrayContainer();
	ArrayContainer( const CoordinateVector& size );
	ArrayContainer( const CoordinateVector& size, ValueType defaultValue );

	/**
	 * @brief Constructor (use pre allocated data).
	 *
	 * @param dataPtr a pointer to the pre allocated data.
	 */
	ArrayContainer(ValueType* dataPtr
		, const CoordinateVector& size
		, const StrideVector& stride
			);

	/**
	 * @brief Destructor.
	 */
	~ArrayContainer();



// -----------------------------------------------------------------
	/**
	 * @brief Returns a pointer to the very first element stored in the container.
	 */
	ValueType * const getDataPointer() const
		{ return _data; }

	
	/**
	 * @brief Returns the total size of the container.
	 *
	 * Equals the number of atomic vale stored.
	 *  = number of components * product of each span size
	 */
	inline kiwi::uint32_t size() const {return _totalSize;}

	/**
	 * @brief Returns the size of a given span.
	 */
	inline kiwi::uint32_t spanSize(kiwi::uint32_t dimension) const
		{ return _spanSize(dimension); }

	/**
	 * @brief Returns a Point<uint32, Dimension> containing the dimensions
	 * of the ArrayConatiner.
	 */
	inline CoordinateVector spanSize() const { return _spanSize; }

	kiwi::uint32_t memoryEstimation() const { return size()*sizeof(ValueType);}
	bool isComposite() const {return false;}
	kiwi::uint32_t nbSubContainers() const {return 0;}

	ValueType getValue( kiwi::uint32_t pos ) const {
		return *(_data + pos * _stride(0));
	}
	void setValue( kiwi::uint32_t pos, ValueType value ){
		*(_data + pos * _stride(0)) = value;
	}
	ValueType getValue( const CoordinateVector& pos ) const {
		ValueType* ptrPos = _data;
		for(kiwi::uint32_t i = 0; i < TDimension; ++i)
			ptrPos += pos(i)*_stride(i);
		return *ptrPos;
	}
	void setValue( const CoordinateVector& pos, ValueType value ){
		ValueType* ptrPos = _data;
		for(kiwi::uint32_t i = 0; i < TDimension; ++i)
			ptrPos += pos(i)*_stride(i);
			
		Debug::print() << static_cast<int>( ptrPos - _data ) << endl();
		
		*ptrPos = value;
	}
	
	/**
	 * @brief Returns this container's stride.
	 *
	 * This is used by the Reader and Writer classes to know how the data
	 * is to be iterated.
	 *
	 * stride[1] = stride[0] * width
	 * stride[2] = stride[1] * width * height
	 * stride[3] = stride[2] * width * height * depth
	 * etc.
	 */
	StrideVector stride() const;

	kiwi::uint32_t stride(kiwi::uint32_t dimension) const;

	/**
	 * @brief Returns true if the buffers are interleaved.
	 *
	 */
	inline bool isInterleaved() { return (_stride[0] != 1); }

	/**
	 * @brief Returns an iterator that iterates through all the data.
	 */
	ArrayIterator<ValueType> getBasicIterator() const;



	/**
	 * Intended for debug purposes...
	 */
	void printState();

	/**
	 * @brief TODO
	 */
	bool resize(const CoordinateVector& newSize, bool keepData = false);


	static kiwi::core::Container* newArrayContainer()
	{
		return new ArrayContainer<TValueType, TDimension>(CoordinateVector(128,128),1);
	}

	static void registerToFactory(kiwi::core::NodeFactory& factory, const kiwi::string& filterId);


protected:

	ValueType* _data;
	bool _deleteDataDestructor;
	kiwi::uint32_t _totalSize;
	CoordinateVector _spanSize;
	StrideVector _stride;

};





}//namespace
}//namespace

#include "ArrayContainer.ih"

#endif
