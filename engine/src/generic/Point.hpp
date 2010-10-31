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
#include <assert.h>
#include <boost/lexical_cast.hpp>
#include "utils/types.hpp"

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
	static Point<CoordType, Dimension> zero(){return Point<CoordType, Dimension>(0.0);}
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
	inline CoordType operator[](unsigned int index) const {return _coordinates[index];}
	inline CoordType& operator()(unsigned int index){return _coordinates[index];}
	inline CoordType operator()(unsigned int index) const {return _coordinates[index];}

	Point<CoordType,TDimension> operator + (const Point<CoordType,TDimension>& point);
	Point<CoordType,TDimension> operator - (const Point<CoordType,TDimension>& point);
	void operator += (const Point<CoordType, TDimension>& point);
	void operator -= (const Point<CoordType, TDimension>& point);
	bool operator == (const Point<CoordType, TDimension>& point);
	bool operator != (const Point<CoordType, TDimension>& point);

/*	template < typename CoordType2 >
	Point<CoordType,TDimension>& operator = (const Point<CoordType2, TDimension>& p);
*/

	Point<CoordType,TDimension>& operator = (const Point<CoordType, TDimension>& p);
	
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
	assert(D>0);
	// No initialization for performances
}
template <typename T, unsigned int D>
Point<T,D>::Point(CoordType x)
{
	assert(D>0);
	_coordinates[0] = x;
	for(unsigned i = 1; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<T,D>::Point(CoordType x, CoordType y)
{
	assert(D>=2);
	_coordinates[0] = x;
	_coordinates[1] = y;
	for(unsigned i = 2; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<T,D>::Point(CoordType x, CoordType y, CoordType z)
{
	assert(D>=3);
	_coordinates[0] = x;
	_coordinates[1] = y;
	_coordinates[2] = z;
	for(unsigned i = 3; i < D; ++i) _coordinates[i] = 0;
}
template <typename T, unsigned int D>
Point<T,D>::Point(CoordType x, CoordType y, CoordType z, CoordType w)
{
	assert(D>=4);
	_coordinates[0] = x;
	_coordinates[1] = y;
	_coordinates[2] = z;
	_coordinates[3] = w;
	for(unsigned i = 4; i < D; ++i) _coordinates[i] = 0;
}

template <typename T, unsigned int D>
Point<T,D>::Point(const Point<CoordType,Dimension>& point)
{
	assert(D>0);
	for(unsigned i = 0; i < D; ++i) _coordinates[i] = point._coordinates[i];
}

template <typename T, unsigned int D>
Point<T,D> Point<T,D>::operator + (const Point<T,D>& point)
{
ScopedBlockMacro(__scop, kiwi::string("Point<")
		+types::str<T>()+","
		+boost::lexical_cast<kiwi::string>(D)
		+">::operator + (Point)")
	Point<T,D> res;
	for(unsigned int i = 0; i < D; ++i)
	{
		res[i] = _coordinates[i] + point._coordinates[i];
__(		Debug::print() << "> " <<  static_cast<float>(_coordinates[i]) <<" + "
					<< static_cast<float>(point._coordinates[i])
					<< " = " << static_cast<float>( res[i] ) << endl();
)//debug
	}
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

ScopedBlockMacro(__scop, kiwi::string("Point<")
		+types::str<T>()+","
		+boost::lexical_cast<kiwi::string>(D)
		+">::operator == (Point)")
	for(unsigned int i = 0; i < D; ++ i)
	{
		DEBUG_ONLY(
		Debug::print() << "> " << static_cast<double>(_coordinates[i]) << " " 
				<< static_cast<double>(point._coordinates[i]) << endl();
		)//DEBUG_ONLY
		if(_coordinates[i] != point._coordinates[i]) return false;
	}
	return true;
}

template <typename T, unsigned int D>
bool Point<T,D>::operator != (const Point<T,D>& point)
{
	for(unsigned int i = 0; i < D; ++ i)
		if(_coordinates[i] != point._coordinates[i]) return true;

	return false;
}

/*
template <typename T1, unsigned int D>
template <typename T2 >
Point<T1,D>& Point<T1,D>::operator = (const Point<T2, D>& p)
{
	if(reinterpret_cast<const Point<T1,D>* >(&p) != this)
		for(unsigned i = 0; i < D; ++i)
			_coordinates[i] 
				= static_cast<T1>(p(i));
	
	return *this;
}
*/
template <typename T, unsigned int D>
Point<T,D>& Point<T,D>::operator = (const Point<T, D>& p)
{
	if(&p != this)
		for(unsigned i = 0; i < D; ++i)
			this->_coordinates[i] = p._coordinates[i];
	
	return *this;
}


}//namespace image
}//namespace kiwi

#endif
