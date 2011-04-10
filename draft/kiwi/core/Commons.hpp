
#ifndef KIWI_CORE_COMMONS_HPP
#define KIWI_CORE_COMMONS_HPP


#include <boost/cstdint.hpp>
#include <string>


namespace kiwi{

typedef unsigned int    uint;
typedef unsigned char   uint8;
typedef boost::uint16_t uint16;
typedef boost::uint32_t uint32;
typedef boost::uint64_t uint64;

typedef char int8;
typedef char char_t;
typedef char byte;
typedef boost::int16_t int16;
typedef boost::int32_t int32;
typedef boost::int64_t int64;

typedef float float_t;
typedef double double_t;

typedef std::string string;
typedef char portIndex_t;

struct true_t{static const int value = 1;};
struct false_t{static const int value = 0;};

struct NullType{ typedef NullType type; };
//enum{ READER, WRITER };

}






// TODO move to Macros.hpp

#define DumpValueMacro( expr ) Debug::print() << #expr << ": " << expr << "\n";



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



#endif
