
#pragma once
#ifndef KIWI_GENERIC_RAWBUFFERCONTAINER_HPP
#define KIWI_GENERIC_RAWBUFFERCONTAINER_HPP

#include "kiwi/generic/ArrayContainerInterface.hpp"

#include <vector>

namespace kiwi{
namespace generic{
	
class RawBufferContainer : public ArrayContainerInterface<kiwi::byte_t,1>
{
public:
	RawBufferContainer( kiwi::uint32_t initSize )
	{
		_data.setSize( initSize );
	}

	// ---- virtual methods from kiwi::core::Container ----
	bool isComposite() const {return false;}
	kiwi::uint32_t nbSubContainers() const {return 0;}
	kiwi::uint32_t size() const {return _data.size();}
	kiwi::uint32_t memoryEstimation() const {return size();}


private:
	std::vector<kiwi::byte_t> _data;
};


#endif
