#ifndef KIWI_FILTER_HPP
#define KIWI_FILTER_HPP

#include "Resource.hpp"


namespace kiwi
{
namespace core
{


	
class Filter : public Resource
{
public:

	/*
	 * Main entry point of the filter. This is the function you should override to perform
	 * whatever the filter is supposed to do.
	 */ 
	virtual void process() = 0;


	Filter():Resource()
	{
	}

	~Filter()
	{
		
	}	


};


/*
bool operator << (const Filter::OutputSlot<Filter::Reader>* out, const Filter::InputSlot<Filter::Reader>* in);
bool operator >> (const Filter::InputSlot<Filter::Writer>* in, const Filter::OutputSlot<Filter::Writer>* out);
*/


}//namespace core
}//namespace kiwi


#endif
