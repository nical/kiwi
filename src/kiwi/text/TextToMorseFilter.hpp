#pragma once

#ifndef KIWI_TEXTTOMORSEFILTER_HPP
#define KIWI_TEXTTOMORSEFILTER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/CanonicalFilter.hpp"
#include "kiwi/core/Tags.hpp"
#include "kiwi/text.hpp"
#include "kiwi/utils/types.hpp"
#include "kiwi/core/NodeFactory.hpp"





namespace kiwi{
namespace text{


class TextToMorseFilter : public core::CanonicalFilter
{
public:
	
	TextToMorseFilter() : CanonicalFilter(1)
	{
	//ScopedBlockMacro(scp_block, "TextToMorseFilter::constructor");
		// CanonicalFilter's constructor automatically adds one reader output port
		// and one writer input port.
		
		addReaderInputPort(); // input text
		addReaderInputPort(); // opt: dot pattern 
		addReaderInputPort(); // opt: long pattern
		addReaderInputPort(); // opt: space pattern
		addReaderInputPort(); // opt: unknown char pattern
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
			addWriteNode(new PlainTextContainer, 0);
		}
	
		TextReader input( readerInputPort(0) );
		TextWriter result( writerInputPort(0) );
		result.clear();
		kiwi::string dotPattern(".");
		kiwi::string longPattern("-");
		kiwi::string spacePattern(" ");
		kiwi::string unknownPattern(" ");
		
		if(readerInputPort(1).isConnected() )
		{
			TextReader r1( readerInputPort(1) );
			dotPattern = r1.line(0).str();
		}
		
		if(readerInputPort(2).isConnected() )
		{
			TextReader r2( readerInputPort(2) );
			longPattern = r2.line(0).str();
		}
		
		if(readerInputPort(3).isConnected() )
		{
			TextReader r3( readerInputPort(3) );
			spacePattern = r3.line(0).str();
		}
		
		if(readerInputPort(4).isConnected() )
		{
			TextReader r4( readerInputPort(4) );
			unknownPattern = r4.line(0).str();
		}
			
		if(input.nbLines() > 1) result.insertLine(kiwi::text::PlainTextLine(""), input.nbLines() -1);	
		
		
		for(uint32_t i = 0; i < input.nbLines(); ++i ){
			result.insertLine(PlainTextLine(""),-1);
			for(uint32_t j = 0; j < input.line(j).size(); ++j ){
				
				kiwi::string morse = charToMorse(input.line(i).getChar(j));
				for(uint32_t k = 0; k < morse.size(); ++k )
					if(morse[k] == '.') result.line(i) += dotPattern;
					else if(morse[k] == '-') result.line(i) += longPattern;
					else if(morse[k] == '#') result.line(i) += unknownPattern;
					else result.line(i) += spacePattern;
			}
		}
		

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
			case ' ' : return kiwi::string(" "); 
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
			default : return kiwi::string ("# ");
			
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
	
	kiwi::Tags readerInputTags( portIndex_t index )
	{
		if(index == 0 ) return kiwi::Tags("#text");
		else return kiwi::Tags("#text#opt");
	}
	// same idea with writer inputs
	kiwi::Tags writerInputTags( portIndex_t index )
	{
		return kiwi::Tags("#text");
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
