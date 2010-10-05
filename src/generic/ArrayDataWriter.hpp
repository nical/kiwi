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

#ifndef KIWI_ARRAYDATAWRITER_HPP
#define KIWI_ARRAYDATAWRITER_HPP

#include "core/Resource.hpp"
#include "generic/ArrayData.hpp"


namespace kiwi
{
namespace generic
{
	
	
template < typename TValueType, unsigned int TDimension>
class ArrayDataWriter : public core::Writer
{
public:
	typedef TValueType ValueType;
	typedef Point<unsigned int, TDimension+1> incsType;
	
	// -----------------------------------------------------------------
	/**
	 * @brief Constructor.
	 */ 
	ArrayDataWriter(const core::Resource::WriterInputPort& port);
	
	/**
	 * @brief Basic access method.
	 */ 
	ValueType get(const Point<int, TDimension>& coords) const;	
	void set(const Point<int, TDimension>& coords, ValueType value);
	
	/**
	 * @brief Unsafe yet faster access method.
	 */ 
	inline const ValueType* getDataPointer() const { return _data; } 	// TODO: const stuff
	
	/**
	 * @brief Returns an iterator to the beguinning of the data.
	 */ 
	ArrayConstIterator<TValueType> begin() const
		{return ArrayConstIterator<ValueType>(_data, _incs); }
	
	/**
	 * @brief Returns an iterator to the end of the data.
	 */ 	
	ArrayConstIterator<TValueType> end() const
		{return ArrayConstIterator<ValueType>(_data, _incs); } 			// TODO !
	
protected:
 ValueType* _data;
 incsType _incs;
 portIndex_t _port;
};


}	
} // namespace


#include "generic/ArrayDataWriter.ih"


#endif
