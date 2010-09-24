#pragma once

#ifndef KIWI_ARRAYREADER_HPP
#define KIWI_ARRAYREADER_HPP

namespace kiwi
{
namespace generic
{
	
	
template < typename TValueType, unsigned int TDimension>	
class ArrayReader : public Reader
{
public:
	typedef TValueType ValueType;
	
	// -----------------------------------------------------------------
	ArrayReader(ValueType* dataPtr, int increments[TDimension+1])
		: _data(dataPtr), _incs(increments) {}
	
	ValueType get(const Point<TValueType, TDimension>& coords) const
	{
		unsigned index = 0;
		for(unsigned i = 0; i < TDimension; ++i)
			index += _incs[i]*coords(i);
			
		return _data[index];
	}
	
	inline const ValueType* getRawPointer(){return _data;}
	
	ArrayConstIterator<TValueType> begin() const
		{return ArrayConstIterator<ValueType>(_data, _incs); }
		
	ArrayConstIterator<TValueType> end() const
		{return ArrayConstIterator<ValueType>(_data, _incs); } // TODO !
		
protected:
 ValueType* _data;
 int _incs[TDimension+1];
};



}	
} // namespace

#endif
