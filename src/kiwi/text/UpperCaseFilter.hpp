#pragma once

#ifndef KIWI_UPPERCASEFILTER_HPP
#define KIWI_UPPERCASEFILTER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Tags.hpp"
#include "kiwi/text/TextReader.hpp"
#include "kiwi/text/TextWriter.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/utils/types.hpp"
#include "kiwi/text/PlainTextContainer.hpp"
#include "kiwi/utils/Factory.hpp"
#include "kiwi/utils/TextOperations.hpp"
#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/ReaderPort.hpp"
#include "kiwi/core/WriterPort.hpp"





namespace kiwi{
namespace text{

/**
 * @brief Copies the input text forcing each character to be upper case.
 */ 
class UpperCaseFilter : public core::Filter
{
public:
	
	UpperCaseFilter() : Filter(/*1*/)
	{
	//ScopedBlockMacro(scp_block, "UpperCaseFilter::constructor");
		// CanonicalFilter's constructor automatically adds one reader output port
		// and one writer input port.
		
		addReaderPort();
	}
	
	~UpperCaseFilter() 
	{
		
	}



	// Main entry point of the filter. This is the method to verride in order to 
	// make the filter do whatever it is supposed to do. 
	void process()
	{
		//ScopedBlockMacro(_cpm, "UpperCaseFilter::process")
	
		if( !writerPort(0).isConnected() )
		{
//			addWriteNode(new PlainTextContainer, 0);
		}
	
		TextReader input( readerPort(0) );
		TextWriter result( writerPort(0) );
		result.clear();
			
		if(input.nbLines() > 1) result.insertLine(PlainTextLine(""), input.nbLines() -1);	
		
		for(uint32_t i = 0; i < input.nbLines(); ++i ){
			result.insertLine(PlainTextLine(""),-1);
			for(uint32_t j = 0; j < input.line(i).size(); ++j ){
				result.line(i) += utils::upperCase( input.line(i).getChar(j) );
			}
		}
	}
	

	bool isReady() const
	{
		return (readerPort(0).isConnected() );
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
	kiwi::Tags writerTags( portIndex_t index )
	{
		return kiwi::Tags("#text");
	}
	
	static Node* newUpperCaseFilter() { return new UpperCaseFilter; }
	
	static bool registerToFactory(kiwi::utils::NodeFactory& factory, const kiwi::string& filterId)
	{
		factory.registerClass( filterId
				, kiwi::utils::NodeFactoryDescriptor(
					newUpperCaseFilter
					, "#Filter#text" )
			);	
		return true;
	}

	
};


}// namespace
}// namespace

#endif
