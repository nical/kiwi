// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/**
 *@file types.hpp 
 *@brief A collection of template functions to retrieve inforrmations about the basic cpp scalar types.
 *@author Nicolas Silva
 */


#ifndef KIWI_UTILS_TYPES_HPP
#define KIWI_UTILS_TYPES_HPP

#include <limits.h>
#include "kiwi/core/Commons.hpp"


/* 
 * To use this macro:
 * switch ( types::id<T>() )
 * {
 *   SwitchTypeMacro( whatIwantToCall<KIWI_SWITCH_TYPE>() )
 * };
 */ 

#define TypeSwitchMacro( __kiwi_call )  \
case types::KIWI_INT8_T : { typedef kiwi::int8_t KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_UINT8_T : { typedef kiwi::uint8_t KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_INT16_T : { typedef kiwi::int16_t KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_UINT16_T : { typedef kiwi::uint16_t KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_INT32_T : { typedef kiwi::int32_t KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_UINT32_T : { typedef kiwi::uint32_t KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_INT64_T : { typedef kiwi::int64_t KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_UINT64_T : { typedef kiwi::uint64_t KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_FLOAT_T : { typedef float KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} \
case types::KIWI_DOUBLE_T : { typedef double KIWI_SWITCH_TYPE;\
 __kiwi_call; break;} 


/**
 * @namespace types
 * The namespace grouping the collection of functions to help with type manipulations in template implementations. 
 */
namespace types
{
	
enum typeEnum{ KIWI_UNDEFINED_T, KIWI_INT8_T, KIWI_UINT8_T, KIWI_INT16_T, KIWI_UINT16_T
	, KIWI_INT32_T, KIWI_UINT32_T, KIWI_INT64_T, KIWI_UINT64_T
	, KIWI_FLOAT_T, KIWI_DOUBLE_T, KIWI_BOOL_T };
	
/**
 * @brief Returns the highest value that can be stored in the type passed as template parameter
 */ 
template<typename T> inline T sup(T var = 0);
/**
 * @brief Returns the lowest value that can be stored in the type passed as template parameter
 */ 
template<typename T> inline T inf(T var = 0);
/**
 * @brief Returns the number of bits of the type passed as template parameter
 */ 
template<typename T> inline unsigned nBits(T var = 0) {return sizeof(T) << 3;}

/**
 * @brief Returns true if the type passed as template parameter is signed
 */ 
template<typename T> inline bool isSigned(T var = 0){ return true; }

/**
 * @brief Returns true if the type passed as template parameter is integer
 */ 
template<typename T> inline bool isInteger(T var = 0) { return true; }

/**
 * @brief Returns true if the type passed as template parameter is a pointer
 */ 
template<typename T> inline bool isPointer(T var = 0){ return true; }

/**
 * @brief Returns true if the type passed as template parameter is a number
 */ 
template<typename T> inline bool isNumber(T var = 0){ return false; }

/**
 * @brief Returns an id of the template type if it is a number.
 */ 
template<typename T> inline typeEnum id() { return KIWI_UNDEFINED_T; }

template<typename T1, typename T2> inline typeEnum
compatibleType(T1 t1 = 0,T2 t2 = 0)
{
	// TODO
	return KIWI_DOUBLE_T;
}



/**
 * @brief Returns a string containing the name of the template type
 */ 
template<typename T> inline const char* str(T var = 0){ return "unknown type"; }

template<typename T1, typename T2> struct SAME_TYPE
{	enum{RESULT = 0 };	};
template<typename T> struct SAME_TYPE<T,T>
{	enum{RESULT = 1 };	};

/**
 * @brief Returns true if T1 and T2 are of the same type;
 */ 
template<typename T1, typename T2> inline bool sameType(T1 var1, T2 var2)
{return SAME_TYPE<T1, T2>::RESULT;}
template<typename T1, typename T2> inline bool sameType()
{return SAME_TYPE<T1, T2>::RESULT;}


// ---------------------------------------------------------------------
template <> inline kiwi::int32_t sup<kiwi::int32_t>(kiwi::int32_t){ return INT_MAX; }
template <> inline kiwi::int32_t inf<kiwi::int32_t>(kiwi::int32_t){ return INT_MIN; }
template <> inline kiwi::uint32_t sup<kiwi::uint32_t>(kiwi::uint32_t){ return UINT_MAX; }
template <> inline kiwi::uint32_t inf<kiwi::uint32_t>(kiwi::uint32_t){ return 0; }

template <> inline kiwi::int16_t sup<kiwi::int16_t>(kiwi::int16_t){ return SHRT_MAX; }
template <> inline kiwi::int16_t inf<kiwi::int16_t>(kiwi::int16_t){ return SHRT_MIN; }
template <>	inline kiwi::uint16_t sup<kiwi::uint16_t>(kiwi::uint16_t){ return USHRT_MAX; }
template <> inline kiwi::uint16_t inf<kiwi::uint16_t>(kiwi::uint16_t){ return 0; }

template <> inline char sup<kiwi::int8_t>(kiwi::int8_t){ return SCHAR_MAX; }
template <> inline char inf<kiwi::int8_t>(kiwi::int8_t){ return SCHAR_MIN; }
template <>	inline kiwi::uint8_t sup<kiwi::uint8_t>(kiwi::uint8_t){ return UCHAR_MAX; }
template <> inline kiwi::uint8_t inf<kiwi::uint8_t>(kiwi::uint8_t){ return 0; }

template <> inline kiwi::int64_t sup<kiwi::int64_t>(kiwi::int64_t){ return LONG_MAX; }
template <> inline kiwi::int64_t inf<kiwi::int64_t>(kiwi::int64_t){ return LONG_MIN; }
template <>	inline kiwi::uint64_t sup<kiwi::uint64_t>(kiwi::uint64_t){ return ULONG_MAX; }
template <> inline kiwi::uint64_t inf<kiwi::uint64_t>(kiwi::uint64_t){ return 0; }

template <> inline bool sup<bool>(bool){ return true; }
template <> inline bool inf<bool>(bool){ return false; }



// ---------------------------------------------------------------------

template <> inline bool isSigned<kiwi::uint8_t>(kiwi::uint8_t){ return false; }
template <> inline bool isSigned<kiwi::uint16_t>(kiwi::uint16_t){ return false; }
template <> inline bool isSigned<kiwi::uint32_t>(kiwi::uint32_t){ return false; }
template <> inline bool isSigned<kiwi::uint64_t>(kiwi::uint64_t){ return false; }
template <> inline bool isSigned<bool>(bool){ return false; }
//template <> inline bool isSigned<void>(){ return false; }


// ---------------------------------------------------------------------

template <> inline bool isInteger<kiwi::float_t>(kiwi::float_t){ return false; }
template <> inline bool isInteger<kiwi::double_t>(kiwi::double_t){ return false; }
//template <> inline bool isInteger<void>(){ return false; }



// ---------------------------------------------------------------------
template <> inline bool isPointer<kiwi::int8_t>(kiwi::int8_t){ return false; }
template <> inline bool isPointer<kiwi::uint8_t>(kiwi::uint8_t){ return false; }
template <> inline bool isPointer<kiwi::int16_t>(kiwi::int16_t){ return false; }
template <> inline bool isPointer<kiwi::uint16_t>(kiwi::uint16_t){ return false; }
template <> inline bool isPointer<kiwi::int32_t>(kiwi::int32_t){ return false; }
template <> inline bool isPointer<kiwi::uint32_t>(kiwi::uint32_t){ return false; }
template <> inline bool isPointer<kiwi::int64_t>(kiwi::int64_t){ return false; }
template <> inline bool isPointer<kiwi::uint64_t>(kiwi::uint64_t){ return false; }
template <> inline bool isPointer<kiwi::float_t>(kiwi::float_t){ return false; }
template <> inline bool isPointer<kiwi::double_t>(kiwi::double_t){ return false; }
template <> inline bool isPointer<bool>(bool){ return false; }
//template <> inline bool isPointer<void>(){ return false; }


// ---------------------------------------------------------------------
template <> inline const char* str<bool>(bool){ return "bool"; }
template <> inline const char* str<kiwi::int8_t>(kiwi::int8_t){ return "int8"; }
template <> inline const char* str<kiwi::uint8_t>(kiwi::uint8_t){ return "uint8"; }
template <> inline const char* str<kiwi::int16_t>(kiwi::int16_t){ return "int16"; }
template <> inline const char* str<kiwi::uint16_t>(kiwi::uint16_t){ return "uint16"; }
template <> inline const char* str<kiwi::int32_t>(kiwi::int32_t){ return "int32"; }
template <> inline const char* str<kiwi::uint32_t>(kiwi::uint32_t){ return "uint32"; }
template <> inline const char* str<kiwi::int64_t>(kiwi::int64_t){ return "int64"; }
template <> inline const char* str<kiwi::uint64_t>(kiwi::uint64_t){ return "uint64"; }
template <> inline const char* str<float>(kiwi::float_t){ return "float"; }
template <> inline const char* str<double>(kiwi::double_t){ return "double"; }
//template <> inline const char* str<void>(){ return "void"; }
template <> inline const char* str<bool*>(bool*){ return "bool*"; }
template <> inline const char* str<kiwi::int8_t*>(kiwi::int8_t*){ return "int8*"; }
template <> inline const char* str<kiwi::uint8_t*>(kiwi::uint8_t*){ return "uint8*"; }
template <> inline const char* str<kiwi::int16_t*>(kiwi::int16_t*){ return "int16*"; }
template <> inline const char* str<kiwi::uint16_t*>(kiwi::uint16_t*){ return "uint16*"; }
template <> inline const char* str<kiwi::int32_t*>(kiwi::int32_t*){ return "int32*"; }
template <> inline const char* str<kiwi::uint32_t*>(kiwi::uint32_t*){ return "uint32*"; }
template <> inline const char* str<kiwi::int64_t*>(kiwi::int64_t*){ return "int64*"; }
template <> inline const char* str<kiwi::uint64_t*>(kiwi::uint64_t*){ return "uint64*"; }
template <> inline const char* str<float*>(kiwi::float_t*){ return "float*"; }
template <> inline const char* str<double*>(kiwi::double_t*){ return "double*"; }


//----------------------------------------------------------------------
template <> inline bool isNumber<kiwi::int8_t>(kiwi::int8_t){ return true; }
template <> inline bool isNumber<kiwi::uint8_t>(kiwi::uint8_t){ return true; }
template <> inline bool isNumber<kiwi::int16_t>(kiwi::int16_t){ return true; }
template <> inline bool isNumber<kiwi::uint16_t>(kiwi::uint16_t){ return true; }
template <> inline bool isNumber<kiwi::int32_t>(kiwi::int32_t){ return true; }
template <> inline bool isNumber<kiwi::uint32_t>(kiwi::uint32_t){ return true; }
template <> inline bool isNumber<kiwi::int64_t>(kiwi::int64_t){ return true; }
template <> inline bool isNumber<kiwi::uint64_t>(kiwi::uint64_t){ return true; }
template <> inline bool isNumber<kiwi::float_t>(kiwi::float_t){ return true; }
template <> inline bool isNumber<kiwi::double_t>(kiwi::double_t){ return true; }

template <> inline typeEnum id<kiwi::int8_t>() { return KIWI_INT8_T; }
template <> inline typeEnum id<kiwi::uint8_t>() { return KIWI_UINT8_T; }
template <> inline typeEnum id<kiwi::int16_t>() { return KIWI_INT16_T; }
template <> inline typeEnum id<kiwi::uint16_t>() { return KIWI_UINT16_T; }
template <> inline typeEnum id<kiwi::int32_t>() { return KIWI_INT32_T; }
template <> inline typeEnum id<kiwi::uint32_t>() { return KIWI_UINT32_T; }
template <> inline typeEnum id<kiwi::int64_t>() { return KIWI_INT64_T; }
template <> inline typeEnum id<kiwi::uint64_t>() { return KIWI_UINT64_T; }
template <> inline typeEnum id<kiwi::float_t>() { return KIWI_FLOAT_T; }
template <> inline typeEnum id<kiwi::double_t>() { return KIWI_DOUBLE_T; }
template <> inline typeEnum id<bool>() { return KIWI_BOOL_T; }

}


template < typename typeT >
struct type
{
	enum { max = 0
	, min = 0
	, nBits = sizeof(typeT)<<3
	, isSigned = 0
	, isInteger = 0
	, isPointer = -1
	, id = types::KIWI_UNDEFINED_T
	};
};

template <> struct type<kiwi::int8_t>
{
	enum { max = 128
	, min = -127
	, nBits = sizeof(kiwi::int8_t)<<3
	, isSigned = 1
	, isInteger = 1
	, isPointer = 0
	, id = types::KIWI_INT8_T
	};
};
template <> struct type<kiwi::uint8_t>
{
	enum { max = 255
	, min = 0
	, nBits = sizeof(kiwi::uint8_t)<<3
	, isSigned = 0
	, isInteger = 1
	, isPointer = 0
	, id = types::KIWI_UINT8_T
	};
};
template <> struct type<kiwi::int16_t>
{
	enum { max = SHRT_MAX
	, min = SHRT_MIN
	, nBits = sizeof(kiwi::int16_t)<<3
	, isSigned = 0
	, isInteger = 1
	, isPointer = 0
	, id = types::KIWI_INT16_T
	};
};
template <> struct type<kiwi::uint16_t>
{
	enum { max = USHRT_MAX
	, min = 0
	, nBits = sizeof(kiwi::uint16_t)<<3
	, isSigned = 0
	, isInteger = 1
	, isPointer = 0
	, id = types::KIWI_UINT16_T
	};
};
template <> struct type<kiwi::int32_t>
{
	enum { max = INT_MAX
	, min = INT_MIN
	, nBits = sizeof(kiwi::int32_t)<<3
	, isSigned = 1
	, isInteger = 1
	, isPointer = 0
	, id = types::KIWI_INT32_T
	};
};
template <> struct type<kiwi::uint32_t>
{
	enum { max = UINT_MAX
	, min = 0
	, nBits = sizeof(kiwi::int32_t)<<3
	, isSigned = 0
	, isInteger = 1
	, isPointer = 0
	, id = types::KIWI_INT32_T
	};
};
template <> struct type<kiwi::int64_t>
{
	enum { max = INT_MAX
	, min = INT_MIN
	, nBits = sizeof(kiwi::int64_t)<<3
	, isSigned = 1
	, isInteger = 1
	, isPointer = 0
	, id = types::KIWI_INT64_T
	};
};
template <> struct type<kiwi::uint64_t>
{
	enum { max = UINT_MAX
	, min = 0
	, nBits = sizeof(kiwi::int64_t)<<3
	, isSigned = 0
	, isInteger = 1
	, isPointer = 0
	, id = types::KIWI_INT64_T
	};
};
template <> struct type<kiwi::float_t>
{
	enum { max = 99999999// TODO !
	, min = -99999999
	, nBits = sizeof(kiwi::float_t)<<3
	, isSigned = 1
	, isInteger = 0
	, isPointer = 0
	, id = types::KIWI_FLOAT_T
	};
};
template <> struct type<kiwi::double_t>
{
	enum { max = 99999999
	, min = -99999999
	, nBits = sizeof(kiwi::double_t)<<3
	, isSigned = 1
	, isInteger = 0
	, isPointer = 0
	, id = types::KIWI_DOUBLE_T
	};
};
#endif
