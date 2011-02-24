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
		float d1 = (_point1-pos).manhatanLength();
		float d2 = (_point2-pos).manhatanLength();
		return (d1*_color1 + d2*_color2)/(d1*d2);
	}

	virtual void setValue( const PointType&, ValueType ){}
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
