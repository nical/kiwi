#pragma once
#ifndef KIWI_GENERIC_RECT_HPP
#define KIWI_GENERIC_RECT_HPP

#include "kiwi/generic/Point.hpp"

namespace kiwi{
namespace generic{

/**
 * @brief generic rectangle class.
 */ 
template<typename TValueType, kiwi::uint32_t TDimension>
class Rect
{
public:
	typedef Point<TValueType, TDimension> PointType;
	typedef TValueType ValueType;
	static const kiwi::uint32_t Dimension = TDimension;

	
	Rect(){} // unsafe default constructor (no init)
	
	Rect(const PointType& size)
	: size(size), position(PointType::zero()) { adjust(); }
	
	Rect(const PointType& pos, const PointType& size)
	: size(size), position(pos) { adjust(); }

	void init(const PointType& pos, const PointType& size){
		this->position = pos;
		this->size = size;
		adjust();
	}
	

	inline void adjust(){
		for(kiwi::uint32_t i = 0; i < TDimension; ++i){
			if(size(i) < 0){
				 position(i) -= size(i);
				size(i) = -size(i);
			}
		}
	}

	PointType position;
	PointType size;

protected:
	
};

}//namespace
}//namespace

#endif
