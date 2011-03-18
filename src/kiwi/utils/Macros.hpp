#ifndef KIWI_MACROS_HPP
#define KIWI_MACROS_HPP

#include "kiwi/config.hpp"

#define INDENTATION_PATTERN 3
#define BEGIN_BLOCK_MESSAGE " Begin block "
#define END_BLOCK_MESSAGE " End block "


#ifdef DEBUG
#define ScopedBlockMacro(message) kiwi::ScopedBlock kiwi_scop##__LINE__(message);
#else
#define ScopedBlockMacro(message) 
#endif



#ifdef DEBUG
#define DEBUG_ONLY( instruction ) instruction
#else
#define DEBUG_ONLY( instruction ) 
#endif

#ifdef KIWI_VERBOSE
#define VERBOSE( instruction ) instruction
#else
#define VERBOSE( instruction ) 
#endif

#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
#define LINUX_ONLY( instruction ) instruction
#define NOT_LINUX( instruction )
#else
#define LINUX_ONLY( instruction ) 
#define NOT_LINUX( instruction ) instruction
#endif





#endif //defined KIWI_MACROS_HPP
