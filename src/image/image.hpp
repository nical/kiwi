#pragma once

#ifndef KIWI_IMAGE_HPP
#define KIWI_IMAGE_HPP

namespace kiwi
{
namespace image
{


template<typename ValueTypeT, unsigned DimensionT>
class GenericImageReader
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	typedef DimensionT Dimension;
	// interface
	virtual ValueType get(const Point<ValueType,Dimension>& coordinates) = 0;
	virtual core::GenericConstIterator<ValueType> begin() = 0;
	virtual core::GenericConstIterator<ValueType> end() = 0;
};


template<typename ValueTypeT, unsigned DimensionT>
class GenericImageWriter
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	typedef DimensionT Dimension;
	// interface
	virtual ValueType get(const Point<ValueType,Dimension>& coordinates) = 0;
	virtual void set(const Point<ValueType,Dimension>& coordinates, ValueType val) = 0;
	virtual core::GenericIterator<ValueType> begin() = 0;
	virtual core::GenericIterator<ValueType> end() = 0;
};



} //namespace image
} //namespace kiwi

#endl
