
#pragma once

#ifndef KIWI_GENERIC_NUMBERCONTAINERINTERFACE_HPP
#define KIWI_GENERIC_NUMBERCONTAINERINTERFACE_HPP

#include "kiwi/core/Container.hpp"

namespace kiwi{	
namespace generic{

template<typename TValueType>
class NumberContainerInterface : public kiwi::core::Container
{
public:
	typedef TValueType ValueType;

	virtual ValueType getValue() const = 0;
	virtual void setValue( ValueType value ) = 0;

	ValueType operator + ( ValueType toAdd) const {
		return getValue() + toAdd;
	}
	ValueType operator - ( ValueType toSub) const {
		return getValue() - toSub;
	}
	ValueType operator = ( ValueType val){
		setValue( val );
		return *this;
	}

	ValueType operator += ( ValueType toAdd) {
		setValue(getValue() + toAdd);
		return *this;
	}
	ValueType operator -= ( ValueType toAdd) {
		setValue(getValue() - toAdd);
		return *this;
	}
	
	ValueType operator == ( ValueType toComp) const {
		return (getValue( toComp ) == toComp);
	}
	ValueType operator > ( ValueType toComp) const {
		return (getValue( toComp ) > toComp);
	}
	ValueType operator < ( ValueType toComp) const {
		return (getValue( toComp ) < toComp);
	}
	
	template<typename T2>
	ValueType operator + ( const NumberContainerInterface<T2>& toAdd ) const{
		return getValue() + toAdd.getValue();
	}
	template<typename T2>
	ValueType operator - ( const NumberContainerInterface<T2>& toSub ) const{
		return getValue() - toSub.getValue();
	}



	// -----------------------------------------------------------------

	Tags tags() const
	{
		return Tags( kiwi::string("#number#") + types::str<ValueType>());
	}
	
	kiwi::uint32_t size() const { return 1; }

	
};

}//namespace	
}//namespace	


#endif
