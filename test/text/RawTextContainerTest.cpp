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

	tc.insertLine( kiwi::text::RawLine( "line foo bar" ), 0  );
	assert( *tc.line(0) == kiwi::text::RawLine( "line foo bar" ) );
}


#ifdef KIWI_TEST_MAIN

int main()
{
	TextContainerTest();
	return 0;
}

#endif
