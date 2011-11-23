
#pragma once
#ifndef KIWI_CORE_COMMONS_HPP
#define KIWI_CORE_COMMONS_HPP

#include <string>

#include <stdint.h>
#include <assert.h>

inline bool kiwi_error( const char* const text ) { return false; }
#define KIWI_NOT_IMPLEMENTED(name) assert( kiwi_error(name" is not implemented yet.") )

namespace kiwi{



typedef std::string string;
typedef int DataAccessFlags;

enum{ READ = 1, WRITE = 2, SIGNAL = 4
    , OPT = 16
    , IN = 64, OUT=128 };


typedef unsigned int uint;
typedef unsigned char uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef char int8;
typedef char byte;



}//namespace

#endif
