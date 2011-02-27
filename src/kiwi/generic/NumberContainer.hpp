
#pragma once

#ifndef KIWI_GENERIC_NUMBERCONTAINER_HPP
#define KIWI_GENERIC_NUMBERCONTAINER_HPP

#include "kiwi/generic/NumberContainerInterface.hpp"
#include "kiwi/utils/types.hpp"

namespace kiwi{
namespace generic{

namespace internals{
	//forward declaration
	template<typename T> kiwi::core::Node* __newNumberContainer();
}


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

	/**
	 * @brief Register the Container to the ContainerFactory
	 */
	virtual bool registerToFactory(kiwi::utils::NodeFactory& factory){
		factory.registerClass( kiwi::string(types::str<ValueType>()) + "Number"
		, kiwi::utils::FactoryDescriptor<kiwi::core::Node>(
			&internals::__newNumberContainer<TValueType>
			, "#Container") 
		);
		return true;
	}
	

private:
	TValueType _data;
};

namespace internals{
	template<typename T>
	kiwi::core::Node* __newNumberContainer(){
		return new kiwi::core::Node( new NumberContainer<T>(0) );
	}
}

}//namespace
}//namespace


#endif
