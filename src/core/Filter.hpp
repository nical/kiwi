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

	/**
	 * Main entry point of the filter. This is the function you should override to perform
	 * whatever the filter is supposed to do.
	 */ 
	virtual void process() = 0;

	bool isReady() {return _ready;}
	
	
	bool isAFilter() {return true;}


	Filter():Resource()
	{
	}

	~Filter()
	{
		
	}

// ---------------------------------------------------------------------	
protected:
	void setReady(bool state) {_ready = state;}

// ---------------------------------------------------------------------
private:
	bool _ready;

};


}//namespace core
}//namespace kiwi


#endif
