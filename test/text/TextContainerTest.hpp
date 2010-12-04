#ifndef KIWI_TEST_TEXTCONTAINER_HPP
#define KIWI_TEST_TEXTCONTAINER_HPP


#include "kiwi/text/TextContainer.hpp"
#include "kiwi/text/TextReader.hpp"
#include "kiwi/text/TextWriter.hpp"
#include "kiwi/utils/modulo.hpp"

void TextContainerTest()
{
ScopedBlockMacro(__scp, "kiwi::test::TextContainer")

	kiwi::text::TextContainer tc;
	
	kiwi::text::TextContainer::ReaderType reader(tc,0);
	kiwi::text::TextContainer::WriterType writer(tc,0);
	
	writer.getLine() = kiwi::string("1st line test");
	
	assert(reader.nbLines() == writer.nbLines() );
	Debug::print() << "nbLines " << reader.nbLines() << endl();
	assert(reader.nbLines() == 1);

	
	writer.insertLine( kiwi::string("2nd line test") );//, 0, kiwi::text::TextWriter::BEFORE );
	Debug::print() << "nbLines " << reader.nbLines() << endl();
	assert(reader.nbLines() == 2);

	
	writer.insertLine( kiwi::string("3rd line test") );//, 0, kiwi::text::TextWriter::BEFORE );
	assert(reader.nbLines() == writer.nbLines() );
	Debug::print() << "nbLines " << reader.nbLines() << endl();
	assert(reader.nbLines() == 3);
	
	
	reader.gotoLine(0);
	assert( reader.getLine() == kiwi::string("1st line test") );
	Debug::print() << "#" << reader.getLine() << endl();
	
	reader.gotoNextLine();
	assert( reader.getLine() == kiwi::string("2nd line test") );
	Debug::print() << "#" << reader.getLine() << endl();
	
	reader.gotoNextLine();
	assert( reader.getLine() == kiwi::string("3rd line test") );
	Debug::print() << "#" << reader.getLine() << endl();
	
	writer.removeLine(1);
	assert(reader.nbLines() == 2);
	
	Debug::endl(3);
	
	reader.gotoLine(0);
	assert(reader.currentLine() == 0);
	
	Debug::print() << "#" << reader.getLine() << endl();
	reader.gotoNextLine();
	Debug::print() << "#"  << reader.getLine() << endl();
	
	Debug::print() << "nbLines " << reader.nbLines() << endl();
	
	writer.removeLine(0);
	Debug::print() << "#" << reader.getLine() << endl();
	
	writer.insertLine(kiwi::string("Added out of the text"), 10);
	reader.gotoLine(0);
	while(reader.currentLine() < reader.nbLines() - 1)
	{
		Debug::print() << "#"<< reader.getLine() << endl();
		reader.gotoNextLine();
	}
	
	writer.gotoLine(3);
	reader.gotoLine(3);
	writer.setChar(0,'a');
	
	
	
	writer.setChar(8, 'h');
	
	Debug::print() << reader.getLine() << endl();
	
	assert(reader.getChar(0) == 'a');
	assert(reader.nbChars() == 8);
	
}




#endif
