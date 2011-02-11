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
#include "kiwi/core/NodeFactory.hpp"
#include "kiwi/utils/TextOperations.hpp"
#include "kiwi/core/Ports.hpp"





namespace kiwi{
namespace text{


class UpperCaseFilter : public core::Filter
{
public:
	
	UpperCaseFilter() : Filter(/*1*/)
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
	
		if( !writerInputPort(0).isConnected() )
		{
//			addWriteNode(new PlainTextContainer, 0);
		}
	
		TextReader input( readerInputPort(0) );
		TextWriter result( writerInputPort(0) );
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
	
	static Node* newUpperCaseFilter() { return new UpperCaseFilter; }
	
	static void registerToFactory(kiwi::core::NodeFactory& factory, const kiwi::string& filterId)
	{
		factory.registerNode( filterId
				, kiwi::core::Descriptor<kiwi::core::Node>(
					"UpperCaseFilter"
					, newUpperCaseFilter
					, "#Filter#text" )
			);
	}

	
};


}// namespace
}// namespace

#endif
