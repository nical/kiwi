#pragma once

#ifndef KIWI_AUDIO_HPP
#define KIWI_AUDIO_HPP

#include "core/GenericIterator.hpp"

namespace kiwi
{
namespace audio
{


//using namespace kiwi;

template<typename ValueTypeT>
class GenericAudioReader
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	
	// interface
	virtual ValueType get() = 0;
	virtual core::GenericConstIterator<ValueType> begin() = 0;
	virtual core::GenericConstIterator<ValueType> end() = 0;
};


template<typename ValueTypeT>
class GenericAudioWriter
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	
	// interface
	virtual ValueType get(unsigned int pos);
	virtual void set(unsigned int pos, ValueType val) = 0;
	virtual core::GenericIterator<ValueType> begin() = 0;
	virtual core::GenericIterator<ValueType> end() = 0;
};



}// namespace
}// namespace

#endif
