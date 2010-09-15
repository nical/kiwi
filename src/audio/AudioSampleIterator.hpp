#pragma once

#ifndef KIWI_AUDIOSAMPLEITERATOR_HPP
#define KIWI_AUDIOSAMPLEITERATOR_HPP

#include "core/GenericIterator.hpp"


namespace kiwi
{
namespace audio
{	



template<typename ValueTypeT>
class AudioSampleIterator : public core::GenericIterator<ValueTypeT>
{
public:
	// typedefs
	typedef ValueTypeT ValueType;

	// methods
	bool operator ++ () {++_data;}
	bool operator -- () {--_data;}
	inline ValueType& operator * () {return _data;}
	bool operator == (const AudioSampleIterator<ValueType>& it) {return (_data == *it);}

protected:
	ValueType* _data;
};

template<typename ValueTypeT>
class AudioSampleConstIterator : public core::GenericConstIterator<ValueTypeT>
{
public:
	// typedefs
	typedef ValueTypeT ValueType;

	// methods
	bool operator ++ () {++_data;}
	bool operator -- () {--_data;}
	inline ValueType operator * () {return _data;}
	bool operator == (const AudioSampleConstIterator<ValueType>& it) {return (_data == *it);}

protected:
	ValueType* _data;
};




}// namespace
}// namespace


#endif
