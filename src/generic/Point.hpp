#pragma once
/**
 * @file Point.hpp
 * @brief a generic point/vector class.
 * @author Nicolas Silva
 * @version 0.1
 */

#ifndef KIWI_POINT_HPP
#define KIWI_POINT_HPP

#include "core/Commons.hpp"

namespace kiwi
{
namespace generic
{


template <typename TCoordType, unsigned int TDimension>
class Point
{
public:
	//typedefs
	typedef TCoordType CoordType;
	static const unsigned int Dimension = TDimension;
	//zero value
	//static const Point<CoordType, TDimension> zero = Point<CoordType, Dimension>(0);

	//constructors
	Point(CoordType* data);
	Point();
	Point(CoordType x);
	Point(CoordType x, CoordType y);
	Point(CoordType x, CoordType y, CoordType z);
	Point(CoordType x, CoordType y, CoordType z, CoordType w);
	Point(const Point<CoordType,Dimension>& point);
	//other methods
	inline CoordType& coordinate(unsigned int index){return _coordinates[index];}
	inline CoordType& operator[](unsigned int index){return _coordinates[index];}
	inline CoordType& operator()(unsigned int index){return _coordinates[index];}

	Point<CoordType,TDimension> operator + (const Point<CoordType,TDimension>& point);
	Point<CoordType,TDimension> operator - (const Point<CoordType,TDimension>& point);
	void operator += (const Point<CoordType, TDimension>& point);
	void operator -= (const Point<CoordType, TDimension>& point);
	bool operator == (const Point<CoordType, TDimension>& point);
	bool operator != (const Point<CoordType, TDimension>& point);	
protected:
	CoordType _coordinates[Dimension];
};





template <typename T, unsigned int D>
Point<T,D>::Point(CoordType* data)
{
	for(unsigned i = 0; i < D; ++i) _coordinates[i] = data[i];
}
template <typename T, unsigned int D>
Point<T,D>::Point()
{
	// No initialization for performances
}
template <typename T, unsigned int D>
Point<T,D>::Point(CoordType x)
{
	_coordinates[0] = x;
	for(unsigned i = 1; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<T,D>::Point(CoordType x, CoordType y)
{
	_coordinates[0] = x;
	_coordinates[1] = y;
	for(unsigned i = 2; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<T,D>::Point(CoordType x, CoordType y, CoordType z)
{
	_coordinates[0] = x;
	_coordinates[1] = y;
	_coordinates[2] = z;
	for(unsigned i = 3; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<T,D>::Point(CoordType x, CoordType y, CoordType z, CoordType w)
{
	_coordinates[0] = x;
	_coordinates[1] = y;
	_coordinates[2] = z;
	_coordinates[3] = w;
	for(unsigned i = 4; i < D; ++i) _coordinates[i] = 0;
}

template <typename T, unsigned int D>
Point<T,D>::Point(const Point<CoordType,Dimension>& point)
{
	for(unsigned i = 0; i < D; ++i) _coordinates[i] = point._coordinates[i];
}

template <typename T, unsigned int D>
Point<T,D> Point<T,D>::operator + (const Point<T,D>& point)
{
	Point<T,D> res;
	for(unsigned int i = 0; i < D; ++ i)
		res[i] = _coordinates[i] + point._coordinates[i];
	return res;
}

template <typename T, unsigned int D>
Point<T,D> Point<T,D>::operator - (const Point<T,D>& point)
{
	Point<T,D> res;
	for(unsigned int i = 0; i < D; ++ i)
		res[i] = _coordinates[i] - point._coordinates[i];
	return res;
}

template <typename T, unsigned int D>
void Point<T,D>::operator += (const Point<T,D>& point)
{
	for(unsigned int i = 0; i < D; ++ i)
		_coordinates[i] += point._coordinates[i];
}

template <typename T, unsigned int D>
void Point<T,D>::operator -= (const Point<T,D>& point)
{
	for(unsigned int i = 0; i < D; ++ i)
		_coordinates[i] -= point._coordinates[i];
}

template <typename T, unsigned int D>
bool Point<T,D>::operator == (const Point<T,D>& point)
{
	for(unsigned int i = 0; i < D; ++ i)
		if(_coordinates[i] != point._coordinates[i]) return false;

	return true;
}

template <typename T, unsigned int D>
bool Point<T,D>::operator != (const Point<T,D>& point)
{
	for(unsigned int i = 0; i < D; ++ i)
		if(_coordinates[i] == point._coordinates[i]) return true;

	return false;
}



}//namespace image
}//namespace kiwi

#endif
