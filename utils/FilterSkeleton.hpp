#pragma once

#ifndef KIWI_FILTEREXAMPLE_HPP
#define KIWI_FILTEREXAMPLE_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/CanonicalFilter.hpp"
#include "kiwi/generic/ArrayReader.hpp"
#include "kiwi/generic/ArrayWriter.hpp"




// ---------------------------------------------------------------------
// --------------------- A simple Filter -------------------------------
// ---------------------------------------------------------------------

namespace kiwi{
namespace tutorial{


class FilterExample : public CanonicalFilter
{
public:
	typedef kiwi::int32_t ValueType;
	static const int Dimension = 2;
	
	typedef generic::ArrayReader<ValueType, Dimension> myReader;
	typedef generic::ArrayWriter<ValueType, Dimension> myWriter;

	/**
	 * @brief constructor.
	 */ 
	FilterExample();
	
	/**
	 * Main entry point of the filter. This is the method to verride 
	 * in order to make the filter do whatever it is supposed to do. 
	 */
	void process();
		

	// This is optionnal. Override this method readyCondition() if this filter
	// needs to perform custom checks to tell if it's ready.
	bool readyCondition();
	
	
	// optionally one can give names to the ports by overriding this...
	kiwi::string readerInputName( portIndex_t index )
	{
		switch index
		{
			case 0 : return kiwi::string("name of the 1st reader input");
			case 1 : return kiwi::string("name of the 2st reader input");
			default : return kiwi::string("error...");
		}
	}
	// ... and these:
	// kiwi::string readerOutputName( portIndex_t index )
	// kiwi::string writerInputName( portIndex_t index )
	
	/* 
	 * optionally, one can also set the input type tags associated to each input 
	 * port. If no tag is defined, the default value is #any which means that any
	 * reader output port can connect to the input port. One can put as many tags
	 * as needed, each tag starting with the '#' character
	 * Example: "#float#array2float"
	 * If several tags are set, the connection will accept outputs using at least
	 * one of the tags. Is the #any tag is present, the input will accept any output
	 */ 
	kiwi::string readerInputType( portIndex_t index )
	{
		return kiwi::string("#array2int32");
	}
	// same idea with writer inputs
	kiwi::string writerInputType( portIndex_t index )
	{
		return kiwi::string("#array2int32");
	}
	
	
};


}// namespace
}// namespace

#endif
