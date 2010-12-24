#ifndef KIWI_MACROS_HPP
#define KIWI_MACROS_HPP

#define INDENTATION_PATTERN 3
#define BEGIN_BLOCK_MESSAGE " Begin block "
#define END_BLOCK_MESSAGE " End block "


#ifdef DEBUG
#define ScopedBlockMacro(vname, message) kiwi::ScopedBlock vname(message);
#else
#define ScopedBlockMacro(vname, message) 
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

#define ParentMacro( pClass ) typedef pClass Parent;


#endif //defined KIWI_MACROS_HPP
