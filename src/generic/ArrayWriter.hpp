#pragma once

#ifndef KIWI_ARRAYWRITER_HPP
#define KIWI_ARRAYWRITER_HPP

namespace kiwi
{
namespace generic
{
	
	
template < typename TValueType, unsigned int TDimension>	
class ArrayWriter : public Writer
{
public:
	typedef TValueType ValueType;
	
	// -----------------------------------------------------------------
	ArrayWriter(ValueType* dataPtr, int increments[TDimension+1])
		: _data(dataPtr), _incs(increments) {}
	
	ValueType get(const Point<TValueType, TDimension>& coords) const
	{
		unsigned index = 0;
		for(unsigned i = 0; i < TDimension; ++i)
			index += _incs[i]*coords(i);
			
		return _data[index];
	}
	
	void set(const Point<TValueType, TDimension>& coords, ValueType value)
	{
		unsigned index = 0;
		for(unsigned i = 0; i < TDimension; ++i)
			index += _incs[i]*coords(i);
			
		_data[index] = value;
	}
	
	inline ValueType* getRawPointer(){return _data;}
	
	ArrayIterator<TValueType> begin() const
		{return ArrayIterator<ValueType>(_data, _incs); }
		
	ArrayIterator<TValueType> end() const
		{return ArrayIterator<ValueType>(_data, _incs); } // TODO !
		
protected:
 ValueType* _data;
 int _incs[TDimension+1];
};



}	
} // namespace

#endif
