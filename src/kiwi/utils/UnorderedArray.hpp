#ifndef KIWI_UTILS_UNORDEREDARRAY_HPP
#define KIWI_UTILS_UNORDEREDARRAY_HPP

#include <vector>
#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace utils{

template<typename T>
class UnorderedArray
{
public:
	static const int NOT_FOUND = -1;

	UnorderedArray(){
		_nbElements = 0;
	}
	
	void add(const T& toCopy){
		_data.push_back( toCopy );
		++_nbElements;
	}
	
	bool remove(const T& toRemove){
		kiwi::int32_t pos = find( toRemove );
		if(pos != NOT_FOUND){
			remove(pos);
		}
	}
	bool remove( kiwi::uint32_t index ){
		if(index >= size() ) return false;
		_data[index] = _data[size()-1];
		--_nbElements;
		return true;
		//TODO: to benchmark: using resize on _data
	}
	
	T& at( kiwi::uint32_t index ) {return _data[index];}
	T at( kiwi::uint32_t index ) const {return _data[index];}
	T& operator[](kiwi::uint32_t index) {return _data[index];}
	T operator[](kiwi::uint32_t index) const {return _data[index];}
	
	bool has(const T& toFind) const {
		for(kiwi::uint32_t i = 0; i < size(); ++i){
			if(_data[i] == toFind) return true;
		}
		return false;
	}

	kiwi::int32_t find(const T& toFind) const {
		for(kiwi::uint32_t i = 0; i < size(); ++i){
			if(_data[i] == toFind) return i;
		}
		return -1;
	}
	
	kiwi::uint32_t size() const { return _nbElements; }


private:
	std::vector<T> _data;
	kiwi::uint32_t _nbElements;
};


};
};


#endif
