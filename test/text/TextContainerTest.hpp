#ifndef KIWI_TEST_TEXTCONTAINER_HPP
#define KIWI_TEST_TEXTCONTAINER_HPP


#include "text/TextContainer.hpp"
#include "text/TextReader.hpp"
#include "text/TextWriter.hpp"
#include "utils/modulo.hpp"

void TextContainerTest()
{
ScopedBlockMacro(__scp, "kiwi::test::TextContainer")

	kiwi::text::TextContainer tc;
	
	kiwi::text::TextContainer::ReaderType reader(tc,0);
	kiwi::text::TextContainer::WriterType writer(tc,0);
	
	writer.getLine() = kiwi::string("1st line test");
	
	
	writer.insertLine( kiwi::string("2st line test") );//, 0, kiwi::text::TextWriter::BEFORE );
	writer.insertLine( kiwi::string("3st line test") );//, 0, kiwi::text::TextWriter::BEFORE );
	reader.gotoLine(0);
	Debug::print() << "#" << reader.getLine() << endl();
	reader.gotoNextLine();
	Debug::print() << "#" << reader.getLine() << endl();
	reader.gotoNextLine();
	Debug::print() << "#" << reader.getLine() << endl();
	writer.removeLine(1);
	
	Debug::endl(3);
	
	reader.gotoLine(0);
	Debug::print() << "#" << reader.getLine() << endl();
	reader.gotoNextLine();
	Debug::print() << "#" << reader.getLine() << endl();
	
	
}




#endif
