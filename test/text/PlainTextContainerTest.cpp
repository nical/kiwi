#include "kiwi/core/Commons.hpp"

#include "kiwi/text/PlainTextContainer.hpp"
#include "kiwi/utils/modulo.hpp"
#include <fstream>

using namespace kiwi;

void PlainTextContainerTest()
{
	ScopedBlockMacro( "kiwi::test::PlainTextContainer")

	kiwi::text::PlainTextContainer tc;
	
	tc.insertLine( kiwi::text::PlainTextLine( "line foo bar" ), 0  );
	tc.insertLine( kiwi::text::PlainTextLine( "kiwi rocks" ), 0 );
	Debug::print() << (tc.line(1)).str() << endl() ;
	
	assert( tc.line(0) == kiwi::text::PlainTextLine( "kiwi rocks" ) );
	assert( tc.line(1) == kiwi::text::PlainTextLine( "line foo bar" ) );
	assert( tc.nbLines() == 2 );
	tc.removeLine(1);
	assert(tc.nbLines() == 1 );
	assert( tc.line(0) == kiwi::text::PlainTextLine( "line foo bar" ) );
	tc.clear();
	assert( tc.nbLines() == 0 );
	tc.insertLine( kiwi::text::PlainTextLine( "line0" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line1" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line2" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line3" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line4" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line5" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line6" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line7" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line8" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line9" ), tc.nbLines() );

	assert( tc.nbLines() == 10 );
	
	

	tc.clear();
	tc.insertLine( kiwi::text::PlainTextLine( "line0" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line1" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line2" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line3" ), tc.nbLines() );
	tc.insertLine( kiwi::text::PlainTextLine( "line4" ), tc.nbLines() );
	assert( tc.nbLines() == 5 );
	tc.removeLines(0, 0);
	assert( tc.nbLines() == 4 );
	tc.removeLines(0, 2);
	assert( tc.nbLines() == 1 );
	
	for(int i = 0; i < tc.nbLines(); ++i)
		Debug::print()<< tc.line(i).str() << endl();
		
}

#ifdef KIWI_TEST_MAIN

int main()
{
	Debug::init(true, true);
	PlainTextContainerTest();
	return 0;
}

#endif
