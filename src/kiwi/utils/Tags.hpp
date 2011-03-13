#pragma once

#ifndef KIWI_CORE_TAGS_HPP
#define KIWI_CORE_TAGS_HPP

#include "kiwi/core/Commons.hpp"

#include <vector>

namespace kiwi{
namespace utils{

class Tags
{
public:

	Tags(){};
	Tags(char const* tagStr);
	Tags(const kiwi::string& tagStr);
	Tags(const Tags& toCopy);
	
	kiwi::string str() const;
	kiwi::string str(kiwi::uint32_t index) const;

	
	Tags tag(kiwi::uint32_t index) const;
	bool hasAll(const Tags& tags) const;
	bool hasOneOf(const Tags& tags) const;
	
	Tags operator+(const Tags& toAdd) const;
	Tags operator-(const Tags& toSub) const;
	Tags& operator+=(const Tags& toAdd); 
	Tags& operator-=(const Tags& toSub);
	bool operator==(const Tags& toComp) const;
	bool operator!=(const Tags& toComp) const;
	Tags operator&&(const Tags& toComp) const;
	Tags& operator&=(const Tags& toComp);
	/**
	 * @brief Returns the number of tags.
	 */ 
	kiwi::uint32_t nb() const {return _data.size();}

	static Tags ANY() {return Tags("any");}

protected:
	void init(char const * str );
	std::vector<kiwi::string> _data;
};

}//namespace
}//namespace

#endif
