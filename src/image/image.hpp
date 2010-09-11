#pragma once

#ifndef KIWI_IMAGE_HPP
#define KIWI_IMAGE_HPP

namespace kiwi
{
namespace image
{
	
template<typename ValueTypeT, unsigned DimensionT>
class ImageReader
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	typedef DimensionT Dimension;
	// interface
	virtual ValueType get(const Point<ValueType,Dimension>& coordinates) = 0;
	virtual ConstIterator<ValueType> begin() = 0;
	virtual ConstIterator<ValueType> end() = 0;
};

template<typename ValueTypeT, unsigned DimensionT>
class ImageWriter
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	typedef DimensionT Dimension;
	// interface
	virtual ValueType get(const Point<ValueType,Dimension>& coordinates) = 0;
	virtual void set(const Point<ValueType,Dimension>& coordinates, ValueType val) = 0;
	virtual Iterator<ValueType> begin() = 0;
	virtual Iterator<ValueType> end() = 0;
};


} //namespace image
} //namespace kiwi

#endl
