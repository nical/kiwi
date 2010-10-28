#pragma once

#ifndef KIWI_ARRAYRESOURCE_HPP
#define KIWI_ARRAYRESOURCE_HPP

#include "core/Resource.hpp"
#include "generic/Point.hpp"


namespace kiwi
{
namespace generic
{



template <typename TValueType, unsigned int TDimension>
class ArrayResource : public core::Resource
{
public:
	typedef TValueType ValueType;
	// -----------------------------------------------------------------------
	virtual ValueType* const getDataPointer(portIndex_t index) const = 0 ;
	virtual Point<unsigned int, TDimension+1> increments(portIndex_t index) const = 0;
	virtual Point<unsigned int, TDimension> spanSize() const = 0;
};



} // neamspace
} // neamspace

#endif
