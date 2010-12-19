#pragma once

#ifndef KIWI_TEXTTOMORSEFILTER_HPP
#define KIWI_TEXTTOMORSEFILTER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/CanonicalFilter.hpp"
#include "kiwi/text.hpp"
#include "kiwi/utils/types.hpp"
#include "kiwi/core/NodeFactory.hpp"





namespace kiwi
{
namespace text
{


class TextToMorseFilter : public core::CanonicalFilter
{
public:
	
	TextToMorseFilter() : CanonicalFilter(1)
	{
	//ScopedBlockMacro(scp_block, "TextToMorseFilter::constructor");
		// CanonicalFilter's constructor automatically adds one reader output port
		// and one writer input port.
		
		addReaderInputPort();
	}
	
	~TextToMorseFilter() 
	{
		
	}



	// Main entry point of the filter. This is the method to verride in order to 
	// make the filter do whatever it is supposed to do. 
	void process()
	{
		//ScopedBlockMacro(_cpm, "TextToMorseFilter::process")
		
		if( !writerInputPort(0).isConnected() )
		{
			addWriteNode(new TextContainer, 0);
		}
	
		TextReader input( readerInputPort(0) );
		TextWriter result( writerInputPort(0) );
		result.reset();
			
		if(input.nbLines() > 1) result.insertLine("", input.nbLines() -1);	
		
		do
		{
			for(uint32_t i = 0; i < input.nbChars(); ++i )
			{
				result.getLine() += charToMorse(input.getChar(i));
			}
			input.gotoNextLine();
			result.gotoNextLine();
		} while(input.currentLine() != input.nbLines()-1 );
		
		return;
	}
	
	kiwi::string charToMorse( char c )
	{
		c = std::toupper(c);
		switch( c )
		{
			case 'A' : return kiwi::string(".- ");   
			case 'B' : return kiwi::string("-... ");
			case 'C' : return kiwi::string("-.-. ");
			case 'D' : return kiwi::string("-.. ");
			case 'E' : return kiwi::string(". ");
			case 'F' : return kiwi::string("..-. ");
			case 'G' : return kiwi::string("-- . ");
			case 'H' : return kiwi::string(".... ");
			case 'I' : return kiwi::string(".. ");
			case 'J' : return kiwi::string(".--- ");
			case 'K' : return kiwi::string("-.- ");
			case 'L' : return kiwi::string(".-.. ");
			case 'M' : return kiwi::string("-- ");
			case 'N' : return kiwi::string("-. ");
			case 'O' : return kiwi::string("--- ");
			case 'P' : return kiwi::string(".--. ");
			case 'Q' : return kiwi::string("--.- ");
			case 'R' : return kiwi::string(".-. ");
			case 'S' : return kiwi::string("... ");
			case 'T' : return kiwi::string("- ");
			case 'U' : return kiwi::string("..- ");
			case 'V' : return kiwi::string("...- ");
			case 'W' : return kiwi::string(".-- ");
			case 'X' : return kiwi::string("-..- ");
			case 'Y' : return kiwi::string("-.-- ");
			case 'Z' : return kiwi::string("--.. ");
			case ' ' : return kiwi::string("  "); 
			case '1' : return kiwi::string(".---- ");
			case '2' : return kiwi::string("..--- ");
			case '3' : return kiwi::string("...-- ");
			case '4' : return kiwi::string("....- ");
			case '5' : return kiwi::string("..... ");
			case '6' : return kiwi::string("-.... ");
			case '7' : return kiwi::string("--... ");
			case '8' : return kiwi::string("---.. ");
			case '9' : return kiwi::string("----. ");
			case '0' : return kiwi::string("----- ");
			default : return kiwi::string ("      ");
			
		}
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
	
	kiwi::string readerInputType( portIndex_t index )
	{
		return kiwi::string("#text");
	}
	// same idea with writer inputs
	kiwi::string writerInputType( portIndex_t index )
	{
		return kiwi::string("#text");
	}
	
	static Filter* newTextToMorseFilter() { return new TextToMorseFilter; }
	
	static void registerToFactory(kiwi::core::NodeFactory& factory, const kiwi::string& filterId)
	{
		factory.registerNode( filterId
				, kiwi::core::Descriptor<kiwi::core::Filter>(
					"TextToMorseFilter"
					, newTextToMorseFilter
					, "#Filter#text" )
			);
	}

	
};


}// namespace
}// namespace

#endif
