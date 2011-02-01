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
class ValueContainerInterface : public core::Container
{
public:
	typedef TValueType ValueType;
	ReaderTypeMacro(ValueReader<ValueType>)
	WriterTypeMacro(ValueWriter<ValueType>)

	/**
	 * @brief returns the value.
	 */
	virtual ValueType getValue() const = 0;
	virtual void setValue( ValueType v ) = 0;

	Tags tags() const
	{
		return Tags( kiwi::string("#value#") + types::str<ValueType>());
	}

	kiwi::uint32_t size() const {return 1;}

};


}//namespace
}//namespace

#endif

