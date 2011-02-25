#pragma once
#ifndef KIWI_IMAGE_LINEARGRADIENTCONTAINER_HPP
#define KIWI_IMAGE_LINEARGRADIENTCONTAINER_HPP

#include "kiwi/generic/PointAccessContainerInterface.hpp"
#include "kiwi/generic/Point.hpp"

namespace kiwi{
namespace image{

template<typename TValueType, kiwi::uint32_t TDimension, typename AccessType>
class LinearGradientContainer
: public generic::PointAccessContainerInterface<TValueType,TDimension,AccessType>
{
public:
	typedef TValueType ValueType;
	static const kiwi::uint32_t Dimension = TDimension;
	typedef generic::Point<AccessType,TDimension> PointType;


	LinearGradientContainer(){}
	
	LinearGradientContainer(
		  const PointType& p1, ValueType c1
		, const PointType& p2, ValueType c2 )
	: _point1(p1), _point2(p2), _color1(c1), _color2(c2)
	{	}

	void init(
		  const PointType& p1, ValueType c1
		, const PointType& p2, ValueType c2 )
	{
		_point1 = p1;
		_point2 = p2;
		_color1 = c1;
		_color2 = c2;
	}

	virtual ValueType getValue( const PointType& pos ) const{
		float dx = 1; //_point2(0) - _point1(0);
		float dy = 1; //_point2(1) - _point1(1);
		float xS = _point1(0) / dx;
		float yS = _point1(1) / dy; 
		float xE = _point2(0) / dx;
		float yE = _point2(1) / dy; 
		float imageX = (float)pos(0) / dx; 
		float imageY = (float)pos(1) / dy;
		float xD = xE - xS; 
		float yD = yE - yS; 
		float mod = 1.0f / ( xD * xD + yD * yD ); 
		float gradPos = ( ( imageX - xS ) * xD + ( imageY - yS ) * yD ) * mod;
		float mag = gradPos > 0 ? gradPos < 1.0f ? gradPos : 1.0f : 0.0f; 
		return _color1*(1-mag) + _color2*(mag); 
	}

	virtual void setValue( const PointType&, ValueType ) {}
	virtual ValueType getValue( kiwi::uint32_t pos ) const {}
	virtual void setValue( kiwi::uint32_t, ValueType ) {}
	PointType spanSize() const { return PointType::zero(); }
	

protected:
	PointType _point1;
	PointType _point2;
	ValueType _color1;
	ValueType _color2;

};


}//namespace
}//namespace


#endif
