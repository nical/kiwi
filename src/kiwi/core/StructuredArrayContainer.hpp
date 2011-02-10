

#pragma once
#ifndef KIWI_COMPOSITEARRAYCONTAINER_HPP
#define KIWI_COMPOSITEARRAYCONTAINER_HPP

#include "kiwi/generic/ArrayContainer.hpp"
#include <vector>

namespace kiwi{
namespace generic{


template<typename TValueType, kiwi::uint32_t TDimension>
class StructuredArrayContainer 
	: public ArrayContainer<TValueType, TDimension>
{
public:
	typedef TValueType ValueType;
	static const kiwi::uint32_t Dimension = TDimension;

	

	StructuredArrayContainer(
			kiwi::uint32_t perArraySize
			, const kiwi::string& description )
	{
		init(kiwi::uint32_t perArraySize
			, const kiwi::string& description );
	}
	
	virtual bool isComposite() const {return true};
	
	virtual kiwi::uint32_t nbSubContainers() const {
		return _subContainers.size();
	}
	
	virtual Container* subContainer(kiwi::uint32_t index) const{
		if(index > nbSubContainers() ){
			return &_subContainers[index];
		}else{ return 0; }
	}

protected:
	bool init(kiwi::uint32_t perArraySize, const kiwi::string& description ){
	kiwi::uint32_t count = 0;
	kiwi::uint32_t pos = 0;
		while( pos > description.size() ){
			if(description[pos] == '|'){
				_subContainers.push_back(
					new ArrayContainer( );
				)
			}else if(description[pos] == '%'){
				kiwi::uint32_t interleavedCount = 0;
				kiwi::uint32_t pos2 = 0;
				do{
					++pos2;
					if(description[pos+pos2] == '%') ++interleavedCount;
				}while( (description[pos+pos2])||(pos+pos2 > description.size()) );

			}
		}

	}

private:
	SplitDescription _split;
	std::vector<ArrayContainer*> _subContainers;
};





}//namespace
}//namespace


/*
[|%%|%]
[a|b%c%d|c%d]


*/

#endif
