#include "Tags.hpp"

#include <assert.h>

namespace kiwi{

void Tags::init(char const* str)
{
	kiwi::uint32_t start = 0;
	kiwi::uint32_t i = 1;
	kiwi::uint32_t nbTags = 0;
	
	while(1)
	{
		if((str[i] == '#')||(str[i] == '\0'))
		{
			bool found = false;
			kiwi::string toAdd = kiwi::string( str + start, i - start );
			for(int j = 0; j < nb(); ++j)
				if( toAdd == _data[j] ) found = true;
				
			if(!found) _data.push_back( toAdd );
			if(str[i] == '\0') break;
			start = i;
		}
		++i;
	}
}

Tags::Tags(char const* str)
{
	init( str );
}

Tags::Tags(const kiwi::string& str)
{
	init( str.c_str() );
}


Tags::Tags(const Tags& toCopy)
{
	_data = toCopy._data;
}

Tags Tags::tag(kiwi::uint32_t index) const
{
	return Tags( _data[index].c_str() );
}

kiwi::string Tags::str() const
{
	kiwi::string result;
	for(uint32_t i = 0; i < _data.size(); ++i)
		result += _data[i];
	return result;
}


kiwi::string Tags::str(kiwi::uint32_t index) const
{
	assert(index < _data.size() );
	return _data[index];
}

bool Tags::hasAll(const Tags& tags) const
{
	if( nb() < tags.nb() ) return false;
	for(uint32_t i = 0; i < tags.nb(); ++i)
	{
		bool found = false;
		for(uint32_t j = 0; j < nb(); ++j)
		{
			if(_data[j] == tags._data[i])
			{
				found = true;
				break;
			}
		}
		if(!found) return false;
	}
	return true;
}

bool Tags::hasOneOf(const Tags& tags) const
{
	for(uint32_t i = 0; i < tags.nb(); ++i)
		for(uint32_t j = 0; j < nb(); ++j)
			if(_data[j] == tags._data[i]) return true;
	
	return false;
}

Tags Tags::operator+(const Tags& toAdd) const
{
	Tags result(*this);
	result += toAdd;
	return result;
}

Tags Tags::operator-(const Tags& toSub) const
{
	Tags result(*this);
	result -= toSub;
	return result;
}

Tags& Tags::operator+=(const Tags& toAdd)
{
	for(uint32_t i = 0; i < toAdd.nb(); ++i ){
		bool add = true;
		for(uint32_t j = 0; j < nb(); ++j )
			// if the tag is already in this, don't add it
			if(_data[j] == toAdd._data[i]){
				add = false;
				break;
			}
		if(add) _data.push_back( toAdd._data[i] );
	}
}

Tags& Tags::operator-=(const Tags& toSub) 
{
	std::vector<kiwi::string>::iterator stop = _data.begin();
	std::vector<kiwi::string>::iterator it = _data.end();
	do{
		--it;
		for(uint32_t i = 0; i < toSub._data.size(); ++i){
			if(*it == toSub._data[i]){
				_data.erase(it);
				break;
			}
		}
	}while(it != stop);
}

bool Tags::operator==(const Tags& toComp) const
{
	if( nb() != toComp.nb() ) return false;
	for(uint32_t i = 0; i < _data.size(); ++i)
	{
		bool found = false;
		for(uint32_t j = 0; j < toComp._data.size(); ++j)
		{
			if(_data[i] == toComp._data[j]){
				found = true;
				break;
			}
		}
		if(!found) return false;
	}
	return true;
}

bool Tags::operator!=(const Tags& toComp) const
{
	return !(*this == toComp); 
}


Tags Tags::operator&&(const Tags& toComp) const
{
	Tags result;
	for(uint32_t i = 0; i < _data.size(); ++i){
		for(uint32_t j = 0; j < toComp._data.size(); ++j){
			if(_data[i] == toComp._data[j] )
				result += Tags( _data[i].c_str() );
		}
	}
	return result;
}

Tags& Tags::operator&=(const Tags& toComp)
{
	std::vector<kiwi::string>::iterator stop = _data.begin();
	std::vector<kiwi::string>::iterator it = _data.end();
	do{
		--it;
		bool found = false;
		for(uint32_t i = 0; i < toComp._data.size(); ++i){
			if(*it == toComp._data[i]){
				found = true;
				break;
			}
		}
		if(!found) _data.erase(it);
	}while(it != stop);
}


}//namespace
