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
 * @version 0.1
 */


#pragma once

#ifndef KIWI_ARRAYDATA_HPP
#define KIWI_ARRAYDATA_HPP

#include "generic/AbstractArrayContainer.hpp"
#include "generic/ArrayReader.hpp"
#include "generic/ArrayWriter.hpp"
#include "generic/Point.hpp"
#include "utils/types.hpp"
#include <boost/lexical_cast.hpp>
#include "generic/ArrayIterator.hpp"

namespace kiwi
{
namespace generic
{


/**
 * @brief Templated container class based on contiguous array buffers.
 * 
 */ 
template<typename TValueType, unsigned int TDimension>
class ArrayContainer : public AbstractArrayContainer<TValueType, TDimension>
{
public:
	typedef TValueType ValueType;
	typedef ArrayReader<TValueType, TDimension> ReaderType;
	typedef ArrayWriter<TValueType, TDimension> WriterType;
	typedef ArrayConstIterator<TValueType> ConstIteratorType;
	typedef ArrayIterator<TValueType> IteratorType;
	typedef AbstractArrayContainer<TValueType, TDimension> Parent;
	
	/**
	 * @brief The Point type used to adress a value in this container.
	 */ 
	typedef Point<unsigned int, TDimension> Coordinates;
	
	/**
	 * @brief The Point type used to contain the increments of this
	 * container.
	 */ 
	typedef Point<unsigned int, TDimension+1> IncsType;
	
	/**
	 * @brief An enum for the constructor's name hint.
	 */ 
	enum{ NUMBERS = 0, RGBA = 1, CMYK = 2, XYZ = 3, ABCD = 4, MONO = 5 };
	enum{ READER_OUT = 0, WRITER_OUT = 1 };
	
	/**
	 * @brief Constructor (allocates the data).
	 * 
	 * @param nbComponents The number of components (and also the number of output ports).
	 * @param interleaved Defines wether or not buffer are interleaved (if nbComponents > 1).
	 * @param nameHint a hint to choose the ports names (see the enums).
	 */ 
	ArrayContainer(Coordinates size
		, unsigned char nbComponents = 1
		, bool interleaved = false
		, unsigned char nameHint = 0 );
		
	/**
	 * @brief Constructor (use pre allocated data).
	 * 
	 * @param dataPtr a pointer to the pre allocated data.
	 * @param nbComponents The number of components (and also the number of output ports).
	 * @param interleaved Defines wether or not buffer are interleaved (if nbComponents > 1).
	 * @param nameHint a hint to choose the ports names (see the enums).
	 */ 
	ArrayContainer(ValueType* dataPtr
		, Coordinates size
		, unsigned char nbComponents = 1
		, bool interleaved = false
		, unsigned char nameHint = 0 );
		
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
	 * Returns a pointer to the data of a given port.
	 * 
	 * Note that if the data is interleaved, the value next to the one 
	 * pointed by the returned pointer does not belong to the data 
	 * associated to the port 
	 * @see increments
	 * @see isInterleaved
	 */ 
	ValueType * const getDataPointer(portIndex_t index) const;
	
	/**
	 * @brief Returns the total size of the container.
	 * 
	 * Equals the number of atomic vale stored.
	 *  = number of components * product of each span size 
	 */ 
	inline unsigned int size() const {return _totalSize;}
	
	/**
	 * @brief Returns the size of a given span.
	 */ 
	inline unsigned int spanSize(unsigned int dimension) const
		{ return _spanSize(dimension); }
		
	/**
	 * @brief Returns a Point<uint32, Dimension> containing the dimensions
	 * of the ArrayConatiner.
	 */ 	
	inline Coordinates spanSize() const { return _spanSize; }
	
	/**
	 * @brief Returns the amount of scalar object referring to one port.
	 * 
	 */ 
	unsigned int oneBufferSize() const;
	
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
	Point<unsigned,TDimension+1> increments(portIndex_t index) const;
	
	/**
	 * @brief Returns true if the buffers are interleaved.
	 * 
	 */ 
	inline bool isInterleaved() { return _interleaved; }
	
	/**
	 * @brief Rturns an iterator that iterates through all the data.
	 */ 
	ArrayIterator<ValueType> getBasicIterator() const;
	
	void printState();
	
	/**
	 * @brief TODO
	 */ 
	bool resize(Coordinates newSize, bool keepData)
	{ assert( "not supported yet" == ""); }
		
	
protected:
	
	/**
	 * @brief A helper method that automatically set the port names given
	 * a family of names.
	 * 
	 * @param index The index of the port. 
	 * @param nameHint the kind of object you are manipulating (see the
	 * enum at the beguinning of the class definition).
	 * @param the port type (Reader/Writer... cf the enum as well). 
	 */ 
	virtual kiwi::string portName(portIndex_t index
		, unsigned char nameHint
		, unsigned char portType = READER_OUT ) const;


private:
	/**
	 * @brief Initializes the container. (called from within the constructors)
	 */ 
	void init(unsigned char nameHint);

	ValueType* _data;
	bool _deleteDataDestructor;
	bool _interleaved;
	unsigned int _totalSize;
	unsigned char _nbComponents;
	Coordinates _spanSize;

};	




	
}//namespace	
}//namespace	

#include "ArrayContainer.ih"

#endif
