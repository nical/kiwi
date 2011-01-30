#pragma once
#ifndef KIWI_GENERIC_ABSTRACTVALUECONAINER_HPP
#define KIWI_GENERIC_ABSTRACTVALUECONAINER_HPP

#include "kiwi/core/Container.hpp" 
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/types.hpp"

namespace kiwi{
namespace generic{

template<typename T> class ValueReader;
template<typename T> class ValueWriter;

template <typename TValueType>
class AbstractValueContainer : public core::Container
{
public:
	typedef TValueType ValueType;
	ReaderTypeMacro(ValueReader<ValueType>)
	WriterTypeMacro(ValueWriter<ValueType>)

	/**
	 * @brief returns the value.
	 */ 
	virtual ValueType& value() = 0;
	virtual const ValueType& value() const = 0;

	Tags tags() const
	{
		return Tags( kiwi::string("#scalar#") + types::str<ValueType>());
	}
	
};


}//namespace
}//namespace

#endif

