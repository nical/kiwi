
#pragma once

#ifndef KIWI_GENERIC_PTRNUMBERCONTAINER_HPP
#define KIWI_GENERIC_PTRNUMBERCONTAINER_HPP

#include "kiwi/generic/NumberContainerInterface.hpp"
#include "kiwi/utils/types.hpp"

namespace kiwi{
namespace generic{


template<typename TValueType>
class PtrNumberContainer : public NumberContainerInterface<TValueType>
{
public:
	typedef TValueType ValueType;

	PtrNumberContainer( ValueType* ptr ) : _data(ptr) {}
	PtrNumberContainer(){
		_data = 0;
	}

	void init(ValueType* val) { _data = val; } 

	ValueType getValue() const{
		return *_data;
	}

	void setValue( ValueType val ){
		*_data = val;
	}

	bool isComposite() const { return false; }
	kiwi::uint32_t nbSubContainers() const { return 0; }
	kiwi::uint32_t memoryEstimation() const { return sizeof(*this); }


private:
	TValueType* _data;
};


}//namespace
}//namespace


#endif
