
#include "DebugOutputStream.hpp"

namespace kiwi{


string endl() 
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m\n";
#else
	return "\n";
#endif
}




}//namespace
