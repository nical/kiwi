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
/**
 * @file Point.hpp
 * @brief a generic point/vector class.
 * @author Nicolas Silva
 * @version 0.1
 */

#ifndef KIWI_POINT_HPP
#define KIWI_POINT_HPP

#include "kiwi/core/Commons.hpp"
#include <assert.h>
#include <boost/lexical_cast.hpp>
#include "kiwi/utils/types.hpp"

namespace kiwi
{
namespace generic
{

/**
 * @brief Generic point/vector class (in the mathematic meaning).
 * 
 */ 
template <typename TCoordType, unsigned int TDimension>
class Point
{
public:
	//typedefs
	typedef TCoordType CoordType;
	static const unsigned int Dimension = TDimension;
	//zero value
	static Point<CoordType, Dimension> zero(){return Point<CoordType, Dimension>(0.0);}
	//constructors
	/**
	 * @brief Constructor (copy from an array)
	 * 
	 * Initializes the Point from a pointer. By contract the array should
	 * contain at least TDimension values 
	 */ 
	Point(CoordType* data);
	
	/**
	 * @brief Constructor (no initialization)
	 * 
	 * For performances this constructor doesn't initializes the data
	 * 
	 */ 
	Point();
	
	/**
	 * @brief Constructor
	 * 
	 * Ititializes the first value to x and the rest to 0.
	 */ 
	Point(CoordType x);
	
	/**
	 * @brief Constructor
	 * 
	 * Ititializes the two first values to x and y and the rest to 0.
	 */ 
	Point(CoordType x, CoordType y);
	
	/**
	 * @brief Constructor
	 * 
	 * Ititializes the three first values to x, y and z and the rest to 0.
	 */ 
	Point(CoordType x, CoordType y, CoordType z);
	
	/**
	 * @brief Constructor
	 * 
	 * Ititializes the four first values to x, y, z and w and the rest to 0.
	 */ 
	Point(CoordType x, CoordType y, CoordType z, CoordType w);
	
	/**
	 * Copy constructor
	 */ 
	Point(const Point<CoordType,Dimension>& point);
	//other methods
	
	/**
	 * @brief Returns a reference to the index'th coordinate.
	 */ 
	inline CoordType& coordinate(unsigned int index){return _coordinates[index];}
	/**
	 * @brief Returns a reference to the index'th coordinate.
	 */ 
	inline CoordType& operator[](unsigned int index){return _coordinates[index];}
	/**
	 * @brief Returns a copy of the index'th coordinate.
	 */ 
	inline CoordType operator[](unsigned int index) const {return _coordinates[index];}
	/**
	 * @brief Returns a reference to the index'th coordinate.
	 */ 
	inline CoordType& operator()(unsigned int index){return _coordinates[index];}
	/**
	 * @brief Returns a copy of the index'th coordinate.
	 */ 
	inline CoordType operator()(unsigned int index) const {return _coordinates[index];}

	/**
	 * @brief Returns the sum of two vectors.
	 */ 
	Point<CoordType,TDimension> operator + (const Point<CoordType,TDimension>& point);
	
	/**
	 * @brief Returns the difference between two vectors.
	 */ 
	Point<CoordType,TDimension> operator - (const Point<CoordType,TDimension>& point);
	
	/**
	 * @brief Increment this vector with another vector.
	 */ 
	void operator += (const Point<CoordType, TDimension>& point);
	
	/**
	 * @brief Decrement this vector with another vector.
	 */ 
	void operator -= (const Point<CoordType, TDimension>& point);
	
	/**
	 * @brief Returns true if the points/vectors are equal.
	 */ 
	bool operator == (const Point<CoordType, TDimension>& point);
	
	/**
	 * @brief Returns false if the points/vectors are equal.
	 */ 
	bool operator != (const Point<CoordType, TDimension>& point);

	/**
	 * @brief Affectation operator.
	 */ 
	Point<CoordType,TDimension>& operator = (const Point<CoordType, TDimension>& p);
	
protected:
	CoordType _coordinates[Dimension];
};





}//namespace image
}//namespace kiwi

#include "Point.ih"

#endif
