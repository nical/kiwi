
#pragma once
#ifndef KIWI_CORE_COMMONS_HPP
#define KIWI_CORE_COMMONS_HPP

#include <string>

#include <boost/cstdint.hpp>

namespace kiwi{



typedef std::string string;
typedef int DataAccessFlags;

enum{ READ = 1, WRITE = 2, SIGNAL = 4
    , OPTIONAL = 16
    , IN = 64, OUT=128 };


typedef unsigned int uint;
typedef unsigned char uint8;
typedef boost::uint16_t uint16;
typedef boost::uint32_t uint32;
typedef boost::uint64_t uint64;
typedef boost::int16_t int16;
typedef boost::int32_t int32;
typedef boost::int64_t int64;
typedef char int8;
typedef char byte;



}//namespace

#endif
