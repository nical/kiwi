
#pragma once

#ifndef KIWI_GENERIC_NUMBERCONTAINER_HPP
#define KIWI_GENERIC_NUMBERCONTAINER_HPP

#include "kiwi/generic/NumberContainerInterface.hpp"

namespace kiwi{
namespace generic{

template<typename TValueType>
class NumberContainer : public NumberContainerInterface<TValueType>
{
public:
	typedef TValueType ValueType;

	NumberContainer( ValueType val ) : _data(val) {}
	NumberContainer() : _data(0) {}

	ValueType getValue() const{
		return _data;
	}

	void setValue( ValueType val ){
		_data = val;
	}

	bool isComposite() const { return false; }
	kiwi::uint32_t nbSubContainers() const { return 0; }
	kiwi::uint32_t memoryEstimation() const { return sizeof(*this); }

private:
	TValueType _data;
};
	

}//namespace
}//namespace


#endif
