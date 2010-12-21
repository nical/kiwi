#include "Tags.hpp"

#include <assert.h>

namespace kiwi{


Tags::Tags(char const* str)
{
	kiwi::uint32_t start = 0;
	kiwi::uint32_t i = 1;
	kiwi::uint32_t nbTags = 0;
	
	while(1)
	{
		if((str[i] == '#')||(str[i] == '\0'))
		{
//			Debug::print() << i << endl();
			_data.push_back( kiwi::string( str + start, i - start ) );
			if(str[i] == '\0') break;
			start = i;
		}
		++i;
	}
}


Tags::Tags(const Tags& toCopy)
{
	_data = toCopy._data;
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
	for(uint32_t i = 0; i < toAdd.nb(); ++i )
		_data.push_back( toAdd._data[i] );
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
		if(_data[i] != toComp._data[i])
			return false;
	return true;
}

bool Tags::operator!=(const Tags& toComp) const
{
	return !(*this == toComp); 
}


}//namespace
