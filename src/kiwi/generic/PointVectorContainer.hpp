
#pragma once
#ifndef KIWI_GENERIC_POINTVECTORCONTAINER_HPP
#define KIWI_GENERIC_POINTVECTORCONTAINER_HPP


#include "kiwi/generic/Point.hpp"
#include "kiwi/core/Tags.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/generic/PtrNumberContainer.hpp"

namespace kiwi{
namespace generic{

template<typename TValueType, kiwi::uint32_t TDimension>
class PointVectorContainer
	: public kiwi::core::Container
	, public kiwi::generic::Point<TValueType, TDimension>
{
public:
	typedef TValueType ValueType;
	typedef kiwi::generic::Point<TValueType, TDimension> PointType;
	enum{ Dimension = TDimension };

	PointVectorContainer(){
		for(kiwi::uint32_t i = 0; i < Dimension; ++i)
			PointType::coordinate(i) = 0;
		initSubContainers();
	}
	
	PointVectorContainer( PointType init ){
		for(kiwi::uint32_t i = 0; i < Dimension; ++i)
			PointType::coordinate(i) = init.coordinate(i);
		initSubContainers();	
	}
	
	virtual Tags tags()const{
		return Tags("#point#vector");
	}

	virtual kiwi::uint32_t size() const{
		return Dimension;
	}
	
	virtual kiwi::uint32_t memoryEstimation() const{
		return sizeof(*this);
	}
	
	virtual bool isComposite() const {return true;}

	virtual kiwi::uint32_t nbSubContainers() const {
		return Dimension;
	}

	virtual kiwi::core::Container* subContainer(kiwi::uint32_t index){
		return &_subContainers[index];
	}

protected:
	kiwi::generic::PtrNumberContainer<ValueType> _subContainers[Dimension] ;

	inline void initSubContainers(){
		for(kiwi::uint32_t i = 0; i < Dimension; ++i)
			_subContainers[i].init(&PointType::_coordinates[i]);
	}
};

}//namespace
}//namespace

#endif
