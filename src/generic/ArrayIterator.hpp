
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
	// constructor
	ArrayIterator(ValueType* dataPtr, unsigned int increment=1) 
	: _data(dataPtr), _increment(increment) {}
	// methods
	bool operator ++ () {_data+=_increment;} 
	bool operator -- () {_data-=_increment;}
	inline ValueType& operator * () {return _data;}
	bool operator == (const ArrayIterator<ValueType>& it) {return (_data == *it);}

protected:
	ValueType* _data;
	unsigned _increment;
};



template<typename ValueTypeT>
class ArrayConstIterator : public GenericConstIterator<ValueTypeT>
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	// constructor
	ArrayConstIterator(ValueType* dataPtr, unsigned int increment=1) 
	: _data(dataPtr), _increment(increment) {}
	// methods
	bool operator ++ () {_data+=_increment;} 
	bool operator -- () {_data-=_increment;}
	inline ValueType operator * () {return _data;}  
	bool operator == (const ArrayConstIterator<ValueType>& it) {return (_data == *it);}

protected:
	ValueType* _data;
	unsigned _increment;
};


}
}
#endif
