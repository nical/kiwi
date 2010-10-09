//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#pragma once

#ifndef KIWI_ARRAYDATA_HPP
#define KIWI_ARRAYDATA_HPP

#include "core/Resource.hpp"
#include "generic/Point.hpp"
#include "utils/types.hpp"
#include <boost/lexical_cast.hpp>

namespace kiwi
{
namespace generic
{



template<typename TValueType, unsigned int TDimension>
class ArrayContainer : public core::Resource
{
public:
	typedef TValueType ValueType;
	typedef Point<unsigned int, TDimension> Coordinates;
	typedef Point<unsigned int, TDimension+1> IncsType;
	
	enum{NUMBERS = 0, RVBA = 1, CMJN = 2, XYZ = 3, ABCD = 4 };
	
	/**
	 * @brief constructor
	 */ 
	ArrayContainer(Coordinates size
		, unsigned char nbComponents = 1
		, unsigned char nameHint = 0 );
	/**
	 * @brief constructor
	 */
	ArrayContainer(ValueType* dataPtr
		, Coordinates size
		, unsigned char nbComponents = 1
		, unsigned char nameHint = 0 );
	/**
	 * @brief destructor
	 */
	~ArrayContainer();


// -----------------------------------------------------------------
	
	ValueType * const getDataPointer() const {return _data;}
	ValueType * const getDataPointer(portIndex_t index) const {return _data + index;}
	
	inline unsigned int size() const {return _totalSize;}
	inline unsigned int spanSize(unsigned int dimension) {return _spanSize(dimension);}
	inline Coordinates spanSize() {return _spanSize;}
	Point<unsigned,TDimension+1> increments(portIndex_t index) const;
	
protected:
	
	virtual kiwi::string portName(portIndex_t index, unsigned char nameHint) const;


private: 
	void init(unsigned char nameHint);

	ValueType* _data;
	bool _deleteDataDestructor;
	unsigned int _totalSize;
	unsigned char _nbComponents;
	Coordinates _spanSize;

};	




	
}//namespace	
}//namespace	

#include "ArrayContainer.ih"

#endif
