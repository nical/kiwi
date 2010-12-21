#pragma once

#ifndef KIWI_CORE_TAGS_HPP
#define KIWI_CORE_TAGS_HPP

#include "kiwi/core/Commons.hpp"

#include <vector>

namespace kiwi{
// this is one of the few classes that is directly within the kiwi namespace
// (along with kiwi::string and a few others...)

class Tags
{
public:
	Tags(char const* tagStr = "#any");
	Tags(const Tags& toCopy);
	
	kiwi::string str() const;
	kiwi::string str(kiwi::uint32_t index) const;
	
	Tags tag(kiwi::uint32_t index);
	
	Tags operator+(const Tags& toAdd) const;
	Tags operator-(const Tags& toSub) const;
	Tags& operator+=(const Tags& toAdd); 
	Tags& operator-=(const Tags& toSub);
	bool operator==(const Tags& toComp) const;
	bool operator!=(const Tags& toComp) const;
	/**
	 * @brief Returns the number of tags.
	 */ 
	kiwi::uint32_t nb() const {return _data.size();}

protected:
	std::vector<kiwi::string> _data;
};

}//namespace

#endif
