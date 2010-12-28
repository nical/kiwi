#include "kiwi/core/Commons.hpp"

#include "kiwi/text/RawTextContainer.hpp"
#include "kiwi/text/TextReader.hpp"
#include "kiwi/text/TextWriter.hpp"
#include "kiwi/utils/modulo.hpp"
#include <fstream>

using namespace kiwi;

void TextContainerTest()
{
ScopedBlockMacro(__scp, "kiwi::test::RawTextContainer")

	kiwi::text::RawTextContainer tc;
	
	kiwi::text::RawTextContainer::ReaderType reader(tc,0);
	kiwi::text::RawTextContainer::WriterType writer(tc,0);
	tc.insertLine( 0, kiwi::text::RawLine( "line foo bar" )  );
	tc.insertLine( 0, kiwi::text::RawLine( "kiwi rocks" ) );
	Debug::print() << (*(tc.line(1))).str() << endl() ;
	assert( *tc.line(0) == kiwi::text::RawLine( "kiwi rocks" ) );
	assert( *tc.line(1) == kiwi::text::RawLine( "line foo bar" ) );
	assert( tc.nbLines() == 2 );
	tc.removeLine(1);
	Debug::print() << tc.nbLines() << endl();
	assert(tc.nbLines() == 1 );
	assert( *tc.line(0) == kiwi::text::RawLine( "line foo bar" ) );
																					
}


#ifdef KIWI_TEST_MAIN

int main()
{
	TextContainerTest();
	return 0;
}

#endif
