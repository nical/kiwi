#pragma once

#ifndef KIWI_FILTERNAME_HPP
#define KIWI_FILTERNAME_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/CanonicalFilter.hpp"
#include "kiwi/generic/ArrayContainer.hpp"
#include "kiwi/generic/ArrayReader.hpp"
#include "kiwi/generic/ArrayWriter.hpp"
#include "kiwi/generic/ArrayIterator.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/utils/types.hpp"

//optionnal (see readerInputType)
#include <boost/lexical_cast.hpp>


// ---------------------------------------------------------------------
// --------------------- A simple Filter -------------------------------
// ---------------------------------------------------------------------

namespace kiwi
{
namespace tutorial
{


class FilterName : public CanonicalFilter
{
public:
	typedef /*scalar type*/ ValueType;
	typedef generic::ArrayReader<ValueType, /*dimension*/> myReader;
	typedef generic::ArrayWriter<ValueType, /*dimension*/> myWriter;


	FilterName() : CanonicalFilter(1)
	{
	ScopedBlockMacro(scp_block, "FilterName::constructor");
		// CanonicalFilter's constructor automatically adds one reader output port
		// and one writer input port.
		
		addReaderInputPort();
		addReaderInputPort();
	}
	
	~AddArraysFilter() 
	{
		
	}



	// Main entry point of the filter. This is the method to verride in order to 
	// make the filter do whatever it is supposed to do. 
	void process()
	{
		// a macro that creates an indentation block and closes it automatically
		// at the end of the scop.
		ScopedBlockMacro(proc_block, "AddArraysFilter::process()");

		Debug::print() << "Allocate Reader #0" << endl();
		myReader A( readerInputPort(0) );
		
		Debug::print() << "Allocate Reader #1" << endl();
		myReader B( readerInputPort(1) );
		
		Debug::print() << "Allocate Writer #0" << endl();
		myWriter result( writerInputPort(0) );
		
		Debug::beginBlock( "compute..");// macro that indents the terminal's output
		
		// you can use kiwi::generic::Point<T,D> to access data in ArrayContainers...
		Point<int, TDimension> pos(0);
		result.set( pos , A.get( pos ) + B.get( pos ) );
		
		// or use iterators...
		ArrayConstIterator<ValueType> itA = A.getIterator();
		ArrayConstIterator<ValueType> itB = B.getIterator();
		ArrayIterator<ValueType> itResult = result.getIterator();
		
		
		unsigned count = 0;
		do
		{
			if( itA.isDone() ) break;
			if( itB.isDone() ) break;
			
			++count;
			
			// do stuff...
			*itResult = *itA + *itB; 
			
			++itA ;
			++itB ;
		} while(itResult.onIteration() );
		
		Debug::print() << count << " iterations " << endl();

		Debug::endBlock( "compute.."); // close the indentation block
		
		return;
	}
	

	// This is optionnal. Override this method readyCondition() if this filter
	// needs to perform custom checks to tell if it's ready.
	bool readyCondition()
	{
		return (readerInputPort(0).isConnected()
			&& readerInputPort(1).isConnected()
			&& writerInputPort(0).isConnected() );
	}
	
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
		return kiwi::string("#array"
				+ boost::lexical_cast<kiwi::string>(/*dimension*/)
				+ types::str<ValueType>() );
	}
	// same idea with writer inputs
	kiwi::string writerInputType( portIndex_t index )
	{
		return kiwi::string("#array"
				+ boost::lexical_cast<kiwi::string>(/*dimension*/)
				+ types::str<ValueType>() );
	}
	
	
};


}// namespace
}// namespace

#endif
