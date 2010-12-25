#pragma once

#ifndef KIWI_UTILS_TERMINAL_HPP
#define KIWI_UTILS_TERMINAL_HPP

namespace kiwi{
namespace utils{
namespace terminal{

/**
 * A collection of functions to tune the terminal's output on Gnu/linux
 * distros.
 */ 

kiwi::string  prefixInfo()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m";
#else
	return "";
#endif
}
kiwi::string  prefixError()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m\033[31m";
	//return "\033[0m\033[31m[ERR]";
#else
	return "";
#endif
}

kiwi::string  prefixWarning()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m\033[35m";
#else
	return "";
#endif
}

kiwi::string  prefixEmphase()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m\033[1m";
#else
	return "";
#endif
}

kiwi::string  postfixReset()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
	return "\033[0m";
#else
	return "";
#endif
}



}//namespace 
}//namespace 
}//namespace 


#endif
