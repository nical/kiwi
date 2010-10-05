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

/**
 * @file ArrayIterator.hpp
 * @brief Header file for the base class of every kiwi resource and filter.
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


template<typename ValueTypeT>
class ArrayIterator : public GenericIterator<ValueTypeT>
{
public:
	// typedefs
	typedef ValueTypeT ValueType;

	// methods
	bool operator ++ () {++_data;} 
	bool operator -- () {--_data;}
	inline ValueType& operator * () {return _data;}
	bool operator == (const ArrayIterator<ValueType>& it) {return (_data == *it);}

protected:
	ValueType* _data;
};



template<typename ValueTypeT>
class ArrayConstIterator : public GenericConstIterator<ValueTypeT>
{
public:
	// typedefs
	typedef ValueTypeT ValueType;

	// methods
	bool operator ++ () {++_data;}
	bool operator -- () {--_data;}
	inline ValueType operator * () {return _data;}
	bool operator == (const ArrayConstIterator<ValueType>& it) {return (_data == *it);}

protected:
	ValueType* _data;
};


}
}
#endif
