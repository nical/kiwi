#pragma once
/**
 * @file Resource.hpp
 * @brief A base class for kiwi resources.
 * @author Nicolas Silva
 * @version 0.1
 */

#ifndef KIWI_POINT_HPP
#define KIWI_POINT_HPP


namespace kiwi
{
namespace image
{


template <typename TCoordType, unsigned int TDimension>
class Point
{
public:
	//typedefs
	typedef TCoordType CoordType;
	typedef TDimension Dimension;
	//zero value
	static const Point<CoordType, Dimension> zero = Point<CoordType, Dimension>(0);

	//constructors
	Point(CoordType* data);
	Point();
	Point(CoordType x, CoordType y);
	Point(CoordType x, CoordType y, CoordType z);
	Point(CoordType x, CoordType y, CoordType z, CoordType w);
	Point(const Point<CoordType,Dimension>& point);
	//other methods
	inline CoordType& coordinate(unsigned int index){return _coordinates[index];}
	inline CoordType& operator[](unsigned int index){return _coordinates[index];}

	Point<CoordType,Dimension> operator + (const Point<CoordType,Dimension>& point);
	Point<CoordType,Dimension> operator - (const Point<CoordType,Dimension>& point);
	void operator += (const Point<CoordType,Dimension>& point);
	void operator -= (const Point<CoordType,Dimension>& point);
protected:
	CoordType _coordinates[Dimension];
};





template <typename T, unsigned int D>
Point<C,D>::Point(CoordType* data)
{
	for(unsigned i = 0; i < D; ++i) _coordinates[i] = data[i];
}
template <typename T, unsigned int D>
Point<C,D>::Point()
{
	for(unsigned i = 0; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<C,D>::Point(CoordType x)
{
	_coordinates[0] = x;
	for(unsigned i = 1; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<C,D>::Point(CoordType x, CoordType y)
{
	_coordinates[0] = x;
	_coordinates[1] = y;
	for(unsigned i = 2; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<C,D>::Point(CoordType x, CoordType y, CoordType z)
{
	_coordinates[0] = x;
	_coordinates[1] = y;
	_coordinates[2] = z;
	for(unsigned i = 3; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<C,D>::Point(CoordType x, CoordType y, CoordType z, CoordType w)
{
	_coordinates[0] = x;
	_coordinates[1] = y;
	_coordinates[2] = z;
	_coordinates[3] = w;
	for(unsigned i = 4; i < D; ++i) _coordinates[i] = 0;
}

template <typename T, unsigned int D>
Point<C,D>::Point(const Point<CoordType,Dimension>& point)
{
	for(unsigned i = 0; i < D; ++i) _coordinates[i] = point._coordinates[i];
}

template <typename C, unsigned int D>
Point<C,D> Point<C,D>::operator + (const Point<C,D>& point)
{
	Point<C,D> res;
	for(unsigned int i = 0; i < D; ++ i)
		res[i] = _coordinates[i] + point._coordinates[i];
	return res;
}

template <typename C, unsigned int D>
Point<C,D> Point<C,D>::operator - (const Point<C,D>& point)
{
	Point<C,D> res;
	for(unsigned int i = 0; i < D; ++ i)
		res[i] = _coordinates[i] - point._coordinates[i];
	return res;
}

template <typename C, unsigned int D>
void Point<C,D>::operator += (const Point<C,D>& point)
{
	for(unsigned int i = 0; i < D; ++ i)
		_coordinates[i] += point._coordinates[i];
}

template <typename C, unsigned int D>
void Point<C,D>::operator -= (const Point<C,D>& point)
{
	for(unsigned int i = 0; i < D; ++ i)
		_coordinates[i] -= point._coordinates[i];
}


}//namespace image
}//namespace kiwi

#endif
