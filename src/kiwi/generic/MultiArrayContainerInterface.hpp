/*
 * 		This file might be useless
 * 	(not much interface to add from ArrayContainer to multiArrayContainer)
 *
 * 	the code might desapear soon...
 */ 



#ifndef KIWI_GENERIC_MULTIARRAYCONTAINER_INTERFACE_HPP 
#define KIWI_GENERIC_MULTIARRAYCONTAINER_INTERFACE_HPP 

#include "kiwi/generic/ArrayContainerInterface.hpp"

namespace kiwi{
namespace generic{


template<typename TValueType, kiwi::uint32_t TDimension>
class MultiArrayContainerInterface 
	: public ArrayContainerInterface<TValueType, TDimension>
{
public:
	typedef TValueType ValueType;
	static const kiwi::uint32_t Dimension = TDimension;

	virtual bool isComposite() const {return true};
}

}//namespace
}//namespace

#endif
