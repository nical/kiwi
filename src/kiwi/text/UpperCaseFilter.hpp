#pragma once

#ifndef KIWI_UPPERCASEFILTER_HPP
#define KIWI_UPPERCASEFILTER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/CanonicalFilter.hpp"
#include "kiwi/core/Tags.hpp"
#include "kiwi/text/TextReader.hpp"
#include "kiwi/text/TextWriter.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/utils/types.hpp"
#include "kiwi/text/PlainTextContainer.hpp"
#include "kiwi/core/NodeFactory.hpp"
#include "kiwi/utils/TextOperations.hpp"





namespace kiwi{
namespace text{


class UpperCaseFilter : public core::CanonicalFilter
{
public:
	
	UpperCaseFilter() : CanonicalFilter(1)
	{
	//ScopedBlockMacro(scp_block, "UpperCaseFilter::constructor");
		// CanonicalFilter's constructor automatically adds one reader output port
		// and one writer input port.
		
		addReaderInputPort();
	}
	
	~UpperCaseFilter() 
	{
		
	}



	// Main entry point of the filter. This is the method to verride in order to 
	// make the filter do whatever it is supposed to do. 
	void process()
	{
		//ScopedBlockMacro(_cpm, "UpperCaseFilter::process")
/*		
		if( !writerInputPort(0).isConnected() )
		{
			addWriteNode(new PlainTextContainer, 0);
		}
	
		TextReader input( readerInputPort(0) );
		TextWriter result( writerInputPort(0) );
		result.reset();
			
		if(input.nbLines() > 1) result.insertLine("", input.nbLines() -1);	
		
		do
		{
			for(uint32_t i = 0; i < input.nbChars(); ++i )
			{
				result.setChar( i, utils::upperCase( input.getChar(i) ));
			}
			input.gotoNextLine();
			result.gotoNextLine();
		} while(input.currentLine() != input.nbLines()-1 );
*/		
	}
	

	// This is optionnal. Override this method readyCondition() if this filter
	// needs to perform custom checks to tell if it's ready.
	bool readyCondition()
	{
		return (readerInputPort(0).isConnected() );
	}
	
	
	kiwi::string readerInputName( portIndex_t index )
	{
		return kiwi::string("in");	
	}
	kiwi::string writerInputName( portIndex_t index )
	{
		return kiwi::string("write");	
	}
	kiwi::string readerOutputName( portIndex_t index )
	{
		return kiwi::string("out");	
	}
	
	kiwi::Tags readerInputTags( portIndex_t index )
	{
		return kiwi::string("#text");
	}
	// same idea with writer inputs
	kiwi::Tags writerInputTags( portIndex_t index )
	{
		return kiwi::Tags("#text");
	}
	
	static Filter* newUpperCaseFilter() { return new UpperCaseFilter; }
	
	static void registerToFactory(kiwi::core::NodeFactory& factory, const kiwi::string& filterId)
	{
		factory.registerNode( filterId
				, kiwi::core::Descriptor<kiwi::core::Filter>(
					"UpperCaseFilter"
					, newUpperCaseFilter
					, "#Filter#text" )
			);
	}

	
};


}// namespace
}// namespace

#endif
