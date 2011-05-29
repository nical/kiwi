
#ifndef KIWI_UTILS_UNORDEREDARRAY_HPP
#define KIWI_UTILS_UNORDEREDARRAY_HPP
#pragma once

#include <vector>
#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace utils{

template<typename T>
class UnorderedArray
{
public:
	static const int NOT_FOUND = -1;
  typedef T* iterator;

	UnorderedArray(){
		_nbElements = 0;
	}
	
	void insert(const T& toCopy){
		_data.push_back( toCopy );
		++_nbElements;
	}
	
	bool remove(const T& toRemove){
		kiwi::int32 pos = findIndex( toRemove );
		if(pos != NOT_FOUND){
			return removeIndex( static_cast<kiwi::uint32>(pos) );
		}else return false;
			
	}
	bool removeIndex( kiwi::uint32 index ){
		if(index >= size() ) return false;
		_data[index] = _data[size()-1];
		--_nbElements;
		return true;
		//TODO: to benchmark: using resize on _data
	}
  void clear(){
    _nbElements = 0;
    _data.resize(0);
  }
	
	T& at( kiwi::uint32 index ) {return _data[index];}
	T at( kiwi::uint32 index ) const {return _data[index];}
	T& operator[](kiwi::uint32 index) {return _data[index];}
	T operator[](kiwi::uint32 index) const {return _data[index];}
	
	bool has(const T& toFind) const {
		for(kiwi::uint32 i = 0; i < size(); ++i){
			if(_data[i] == toFind) return true;
		}
		return false;
	}

	T* find(const T& toFind) {
		for(kiwi::uint32 i = 0; i < size(); ++i){
			if(_data[i] == toFind) return &(_data[i]);
		}
		return 0;
	}
	const T* find(const T& toFind) const {
		for(kiwi::uint32 i = 0; i < size(); ++i){
			if(_data[i] == toFind) return &(_data[i]);
		}
		return 0;
	}
  
	kiwi::int32 findIndex(const T& toFind) const {
		for(kiwi::uint32 i = 0; i < size(); ++i){
			if(_data[i] == toFind) return i;
		}
		return -1;
	}
	
	kiwi::uint32 size() const { return _nbElements; }

  iterator begin() { return &_data[0]; }
  iterator end() { return begin() + _nbElements; }


private:
	std::vector<T> _data;
	kiwi::uint32 _nbElements;
};


}//namespace
}//namespace



#endif
