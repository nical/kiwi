#ifndef KIWI_FILTER_HPP
#define KIWI_FILTER_HPP

#include "Resource.hpp"
#include "Filter.hpp"

namespace kiwi
{


	
class Pipeline : public Filter
{
public:
	Pipeline(unsigned nbInputReaders, unsigned nbOutputReaders,
			unsigned nbInputWriters, unsigned nbOutputWriters)
		:Resource(nbInputReaders, nbOutputReaders, nbInputWriters, nbOutputWriters)
	{
	}

	virtual bool addFilter(Filter* filter);

private:
	Pipeline* _pipeline;
	Filter(unsigned _nbInputReaders, unsigned _nbOutputReaders,
		unsigned _nbInputWriters, unsigned _nbOutputWriters);

};



}//namespace kiwi



#endif
