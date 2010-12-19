#include "TextOperations.hpp"

#include <string>

namespace kiwi{
namespace utils{ 

char upperCase( char c )
{
	// TODO : handle special characters like 'é'
	return std::toupper( c );
}
	
char lowerCase( char c )
{
	return std::tolower( c );
}


	
}// namespace
}// namespace
