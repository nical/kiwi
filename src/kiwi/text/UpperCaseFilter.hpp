#pragma once

#ifndef KIWI_UPPERCASEFILTER_HPP
#define KIWI_UPPERCASEFILTER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/Tags.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/utils/types.hpp"
#include "kiwi/text/PlainTextContainer.hpp"
#include "kiwi/utils/Factory.hpp"
#include "kiwi/utils/TextOperations.hpp"
#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/StaticPorts.hpp"
#include "kiwi/core/DynamicNode.hpp"





namespace kiwi{
namespace text{

/**
 * @brief Copies the input text forcing each character to be upper case.
 */ 
class UpperCaseFilter : public core::DynamicNode
{
public:
	
	UpperCaseFilter() : DynamicNode()
	{
		addReaderPort( _reader = new kiwi::core::StaticReaderPort<PlainTextContainer>(this) );
		addWriterPort( _writer = new kiwi::core::StaticWriterPort<PlainTextContainer>(this) );
		addDataPort();
	}
	
	~UpperCaseFilter() 
	{
		
	}



	// Main entry point of the filter. This is the method to verride in order to 
	// make the filter do whatever it is supposed to do. 
	void process()
	{
    ScopedBlockMacro("UpperCaseFilter::process")

    PlainTextContainer* result = _writer->getContainer();
    const PlainTextContainer* input = _reader->getContainer();

    assert(result);
    assert(input);
    
		result->clear();
			
		if(input->nbLines() > 1) result->insertLine(PlainTextLine(""), input->nbLines() -1);	
		
		for(uint32_t i = 0; i < input->nbLines(); ++i ){
			result->insertLine(PlainTextLine(""),-1);
			for(uint32_t j = 0; j < input->line(i).size(); ++j ){
				result->line(i) += utils::upperCase( input->line(i).getChar(j) );
			}
		}
	}
	

	bool isReady() const {
		return (readerPort(0).isConnected() );
	}
	
	kiwi::utils::Tags readerTags( portIndex_t index ) const {
		return kiwi::utils::Tags("#text");
	}
	// same idea with writer inputs
	kiwi::utils::Tags writerTags( portIndex_t index ) const	{
		return kiwi::utils::Tags("#text");
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

protected:
  kiwi::core::StaticReaderPort<PlainTextContainer>* _reader;
  kiwi::core::StaticWriterPort<PlainTextContainer>* _writer;
};


}// namespace
}// namespace

#endif
