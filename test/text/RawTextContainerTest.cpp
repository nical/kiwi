#include "kiwi/core/Commons.hpp"

#include "kiwi/text/RawTextContainer.hpp"
#include "kiwi/text/TextReader.hpp"
#include "kiwi/text/TextWriter.hpp"
#include "kiwi/utils/modulo.hpp"
#include <fstream>

using namespace kiwi;

void RawTextContainerTest()
{
	ScopedBlockMacro(__scp, "kiwi::test::RawTextContainer")

	kiwi::text::RawTextContainer tc;
	
	tc.insertLine( 0, kiwi::text::RawTextLine( "line foo bar" )  );
	tc.insertLine( 0, kiwi::text::RawTextLine( "kiwi rocks" ) );
	Debug::print() << (*(tc.line(1))).str() << endl() ;
	
	assert( *tc.line(0) == kiwi::text::RawTextLine( "kiwi rocks" ) );
	assert( *tc.line(1) == kiwi::text::RawTextLine( "line foo bar" ) );
	assert( tc.nbLines() == 2 );
	tc.removeLine(1);
	assert(tc.nbLines() == 1 );
	assert( *tc.line(0) == kiwi::text::RawTextLine( "line foo bar" ) );
	tc.clear();
	assert( tc.nbLines() == 0 );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line0" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line1" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line2" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line3" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line4" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line5" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line6" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line7" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line8" ) );
	tc.insertLine( tc.nbLines(), kiwi::text::RawTextLine( "line9" ) );

	assert( tc.nbLines() == 10 );
	
	kiwi::text::TextReader read( tc, 0 );

	for( int i = 0; i < read.nbLines(); ++i){
		Debug::print() << read.line(i).str() << endl();
	}
	assert( read.line(0) == kiwi::text::RawTextLine( "line0" ) );
	assert( read.line(1) == kiwi::text::RawTextLine( "line1" ) );
	assert( read.line(2) == kiwi::text::RawTextLine( "line2" ) );
	assert( read.line(3) == kiwi::text::RawTextLine( "line3" ) );

	kiwi::text::TextReader read3_6( tc, 0, 3, 4 ); // range: from lines 3 to 6
	for( int i = 0; i < read3_6.nbLines(); ++i){
//		Debug::print() << read3_6.line(i).str() << endl();
	}
	assert( read3_6.line(0) == kiwi::text::RawTextLine( "line3" ) );
	assert( read3_6.line(1) == kiwi::text::RawTextLine( "line4" ) );
	assert( read3_6.line(2) == kiwi::text::RawTextLine( "line5" ) );
	assert( read3_6.line(3) == kiwi::text::RawTextLine( "line6" ) );
	assert( read3_6.line(-1) == kiwi::text::RawTextLine( "line6" ) );
	Debug::print() << read3_6.line(-1).str() << endl();
	Debug::print() << read3_6.line(-2).str() << endl();
	Debug::print() << read3_6.line(-3).str() << endl();
	assert( read3_6.line(-2) == kiwi::text::RawTextLine( "line5" ) );

	kiwi::text::TextReader subReader = read.readerOnRange(3, 8);
	for( int i = 0; i < subReader.nbLines(); ++i){
		Debug::print() << subReader.line(i).str() << endl();
	}
	assert( subReader.nbLines() == 6 );
}


#ifdef KIWI_TEST_MAIN

int main()
{
	Debug::init(true, true);
	RawTextContainerTest();
	return 0;
}

#endif
