#ifndef KIWI_FILTER_HPP
#define KIWI_FILTER_HPP

#include "core/Resource.hpp"
#include "core/Filter.hpp"
#include "core/Commons.hpp"

#include <list>

namespace kiwi
{
namespace core
{

	
class Pipeline : public Filter
{
public:
	Pipeline()
		:Filter()
	{
		ScopedBlockMacro(s1, "kiwi::core::Pipeline: constructor");

	}

	bool contains(Filter* filter)
	{
		for(std::list<Filter*>::iterator it = _filterList.begin();
			it != _filterList.end(); ++it)
		{
			if(*it = filter) return true;
		}
		return false;
	}

	bool addFilter(Filter& toAdd)
	{
		if(!contains(&toAdd))
		{
			_filterList.push_front(toAdd);
			return true;
		}
		return false;
	}

	void Process()
	{
		std::list<Filter*> readyList;
		std::list<Filter*> todo;
	}

private:
	std::list<Filter*> _filterList;
};




}//namespace core
}//namespace kiwi



#endif
