
#pragma once
#ifndef KIWI_GENERIC_RECTANGLECONTAINER_HPP
#define KIWI_GENERIC_RECTANGLECONTAINER_HPP

#include "kiwi/core/Container.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/generic/PointVectorContainer.hpp"
#include <boost/lexical_cast.hpp>

namespace kiwi{
namespace generic{
	
template<kiwi::uint32_t TDimension>	
class RectangleContainer : public core::Container
{
public:
	static const kiwi::uint32_t Dimension = TDimension;
	typedef generic::Point<kiwi::int32_t, Dimension> PointType;
	
	RectangleContainer(const PointType& upperLeft, const PointType& size)
	{
		_pos.init( upperLeft );
		_size.init( size );
		for(kiwi::uint32_t i = 0; i < Dimension; ++i ){
			if(size(i) < 0){
				_pos(i) += _size(i);
				_size(i) = -_size(i);
			}
		}
	}
	
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
	
	//shortcuts mainly useful in 2d
	kiwi::int32_t left() const { return _pos(0); }
	kiwi::int32_t right() const { return _pos(0)+_size(0); }
	kiwi::int32_t top() const { return _pos(1); }
	kiwi::int32_t bottom() const { return _pos(1)+_size(1); }
	kiwi::int32_t width() const { return _size(0); }
	kiwi::int32_t height() const { return _size(1); }

	virtual bool isComposite() const { return true; }
	virtual kiwi::uint32_t nbSubContainers() const { return 2; }
	virtual kiwi::core::Container* subContainer(kiwi::uint32_t index){
		if(index == 0) return &_pos;
		else if(index == 1) return &_size;
		else return 0;	
	}

	virtual kiwi::Tags tags() {
		return kiwi::Tags(kiwi::string("#rectangle")
			+ boost::lexical_cast<kiwi::string>(TDimension) ); }

protected:
	generic::PointVectorContainer<kiwi::int32_t,Dimension> _pos;
	generic::PointVectorContainer<kiwi::int32_t,Dimension> _size;

	void initSubContainers();
};


}//namespace
}//namespace


#endif
