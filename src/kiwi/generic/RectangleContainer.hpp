
#pragma once
#ifndef KIWI_GENERIC_RECTANGLECONTAINER_HPP
#define KIWI_GENERIC_RECTANGLECONTAINER_HPP

#include "kiwi/core/Container.hpp"
#include "kiwi/generic/Rect.hpp"
#include "kiwi/generic/PointVectorContainer.hpp"
#include <boost/lexical_cast.hpp>

namespace kiwi{
namespace generic{

/**
 * @brief Generic rectangle container implementation.
 */ 	
template<typename TValueType, kiwi::uint32_t TDimension>	
class RectangleContainer : public core::Container
{
public:
	static const kiwi::uint32_t Dimension = TDimension;
	typedef generic::Point<TValueType, TDimension> PointType;
	typedef TValueType ValueType;

	template<typename T>
	RectangleContainer(const Point<T,2>& upperLeft, const Point<T,2>& size)
	{
		_posSubContainer.init( upperLeft ); 
		_sizeSubContainer.init( size );
		adjust();
	}
	
	//generic access
	PointType getPosition() const {
		return _posSubContainer;
	}

	void setPosition( const PointType& value ) {
		_posSubContainer.init( value );
	}
	
	PointType getSize() const{
		return _sizeSubContainer;
	}
	
	void setSize( const PointType& value ){
		_sizeSubContainer.init( value );
		adjust();
	}

	void adjust(){
		for(kiwi::uint32_t i = 0; i < TDimension; ++i){
			if(_sizeSubContainer(i) < 0){
				_posSubContainer(i) += _sizeSubContainer(i);
				_sizeSubContainer(i) = -_sizeSubContainer(i);
			}
		}
	}
	
	//shortcuts mainly useful in 2d
	kiwi::int32_t left() const { return _posSubContainer(0); }
	kiwi::int32_t right() const { return _posSubContainer(0)+_sizeSubContainer(0); }
	kiwi::int32_t top() const { return _posSubContainer(1); }
	kiwi::int32_t bottom() const { return _posSubContainer(1)+_sizeSubContainer(1); }
	kiwi::int32_t width() const { return _sizeSubContainer(0); }
	kiwi::int32_t height() const { return _sizeSubContainer(1); }

	generic::PointVectorContainer<kiwi::int32_t,Dimension>* positionSubContainer(){
		return &_posSubContainer;
	}
	generic::PointVectorContainer<kiwi::int32_t,Dimension>* sizeSubContainer(){
		return &_sizeSubContainer;
	}

	Rect<TValueType, TDimension> rect() const{
		return Rect<TValueType, TDimension>(_posSubContainer,_sizeSubContainer);
	}


	virtual bool isComposite() const { return true; }
	virtual kiwi::uint32_t nbSubContainers() const { return 2; }
	virtual kiwi::core::Container* subContainer(kiwi::uint32_t index){
		if(index == 0) return &_posSubContainer;
		else if(index == 1) return &_sizeSubContainer;
		else return 0;	
	}

	virtual kiwi::Tags tags() {
		return kiwi::Tags(kiwi::string("#rectangle")
			+ boost::lexical_cast<kiwi::string>(TDimension) ); }

protected:
	generic::PointVectorContainer<kiwi::int32_t,Dimension> _posSubContainer;
	generic::PointVectorContainer<kiwi::int32_t,Dimension> _sizeSubContainer;

};


}//namespace
}//namespace


#endif
