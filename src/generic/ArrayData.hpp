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



template<typename TValueType, unsigned int TDimension, unsigned int TComponents>
class ArrayData : public core::Resource
{
public:
	typedef TValueType ValueType;
	typedef Point<unsigned int, TDimension> Coordinates;
	
	enum{NUMBERS = 0, RVBA = 1, CMJN = 2, XYZ = 3, ABCD = 4 };
	
	ArrayData(Coordinates size, unsigned char nameHint = 0);
	~ArrayData();
	
// --------------------------------------------------------- Overloading



// -----------------------------------------------------------------
	
	ValueType * const getRawPointer() const;
	
	inline unsigned int size() const {return _totalSize;}
	inline unsigned int spanSize(unsigned int dimension);
	
protected:
	
	virtual kiwi::string portName(portIndex_t index, unsigned char nameHint) const;



	ValueType* _data;
	bool _deleteDataDestructor;
	unsigned int _totalSize;
	Point<unsigned, TDimension> _spanSize;

};	





	
}//namespace	
}//namespace	

#include "ArrayData.ih"

#endif
