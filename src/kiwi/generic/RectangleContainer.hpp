
#pragma once
#ifndef KIWI_GENERIC_RECTANGLECONTAINER_HPP
#define KIWI_GENERIC_RECTANGLECONTAINER_HPP

#include "kiwi/core/Container.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/generic/PointVectorContainer.hpp"

namespace kiwi{
namespace generic{
	
template<kiwi::uint32_t TDimension>	
class RectangleContainer : public core::Container
{
public:
	enum { Dimension = TDimension };
	typedef generic::Point<kiwi::int32_t, Dimension> PointType;
	
	RectangleContainer(const PointType& upperLeft, const PointType& size)
	{
		_pos.init( upperLeft );
		_size.init( size );
	}

	//RectangleContainer(kiwi::int32_t left, kiwi::int32_t top, kiwi::int32_t width, kiwi::int32_t height )
	
	//generic access
	PointType getPosition() const {
		return _pos;
	}

	void setPosition( const PointType& value ) {
		_pos.init( value );
	}
	
	PointType getSize() const{
		return _size;
	}
	
	void setSize( const PointType& value ){
		_pos.init( value );
	}
	
	//shortcuts maily useful in 2d
	kiwi::int32_t left() const;
	kiwi::int32_t right() const;
	kiwi::int32_t top() const;
	kiwi::int32_t bottom() const;
	kiwi::int32_t width() const;
	kiwi::int32_t height() const;

	virtual bool isComposite() const { return true; }
	virtual kiwi::uint32_t nbSubContainers() const { return 2; }
	virtual kiwi::core::Container* subContainer(kiwi::uint32_t index){
		if(index == 0) return &_pos;
		else if(index == 1) return &_size;
		else return 0;	
	}

protected:
	generic::PointVectorContainer<kiwi::int32_t,Dimension> _pos;
	generic::PointVectorContainer<kiwi::int32_t,Dimension> _size;

	void initSubContainers();
};


}//namespace
}//namespace


#endif
