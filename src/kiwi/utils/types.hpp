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
	, KIWI_FLOAT_T, KIWI_DOUBLE_T };
	
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
template <> inline int sup<int>(int){ return INT_MAX; }
template <> inline int inf<int>(int){ return INT_MIN; }
template <> inline unsigned int sup<unsigned int>(unsigned int){ return UINT_MAX; }
template <> inline unsigned int inf<unsigned int>(unsigned int){ return 0; }

template <> inline short sup<short>(short){ return SHRT_MAX; }
template <> inline short inf<short>(short){ return SHRT_MIN; }
template <>	inline unsigned short sup<unsigned short>(unsigned short){ return USHRT_MAX; }
template <> inline unsigned short inf<unsigned short>(unsigned short){ return 0; }

template <> inline char sup<char>(char){ return SCHAR_MAX; }
template <> inline char inf<char>(char){ return SCHAR_MIN; }
template <>	inline unsigned char sup<unsigned char>(unsigned char){ return UCHAR_MAX; }
template <> inline unsigned char inf<unsigned char>(unsigned char){ return 0; }

template <> inline long sup<long>(long){ return LONG_MAX; }
template <> inline long inf<long>(long){ return LONG_MIN; }
template <>	inline unsigned long sup<unsigned long>(unsigned long){ return ULONG_MAX; }
template <> inline unsigned long inf<unsigned long>(unsigned long){ return 0; }

template <> inline bool sup<bool>(bool){ return true; }
template <> inline bool inf<bool>(bool){ return false; }



// ---------------------------------------------------------------------

template <> inline bool isSigned<unsigned int>(unsigned int){ return false; }
template <> inline bool isSigned<unsigned char>(unsigned char){ return false; }
template <> inline bool isSigned<unsigned short>(unsigned short){ return false; }
template <> inline bool isSigned<unsigned long>(unsigned long){ return false; }
template <> inline bool isSigned<bool>(bool){ return false; }
//template <> inline bool isSigned<void>(){ return false; }


// ---------------------------------------------------------------------

template <> inline bool isInteger<float>(float){ return false; }
template <> inline bool isInteger<double>(double){ return false; }
//template <> inline bool isInteger<void>(){ return false; }



// ---------------------------------------------------------------------
template <> inline bool isPointer<int>(int){ return false; }
template <> inline bool isPointer<unsigned int>(unsigned int){ return false; }
template <> inline bool isPointer<short>(short){ return false; }
template <> inline bool isPointer<unsigned short>(unsigned short){ return false; }
template <> inline bool isPointer<char>(char){ return false; }
template <> inline bool isPointer<unsigned char>(unsigned char){ return false; }
template <> inline bool isPointer<long>(long){ return false; }
template <> inline bool isPointer<unsigned long>(unsigned long){ return false; }
template <> inline bool isPointer<float>(float){ return false; }
template <> inline bool isPointer<double>(double){ return false; }
//template <> inline bool isPointer<void>(){ return false; }


// ---------------------------------------------------------------------
template <> inline const char* str<bool>(bool){ return "bool"; }
template <> inline const char* str<int>(int){ return "int"; }
template <> inline const char* str<unsigned int>(unsigned int){ return "unsigned int"; }
template <> inline const char* str<short>(short){ return "short"; }
template <> inline const char* str<unsigned short>(unsigned short){ return "unsigned short"; }
template <> inline const char* str<char>(char){ return "char"; }
template <> inline const char* str<unsigned char>(unsigned char){ return "unsigned char"; }
template <> inline const char* str<long>(long){ return "long"; }
template <> inline const char* str<unsigned long>(unsigned long){ return "unsigned long"; }
template <> inline const char* str<float>(float){ return "float"; }
template <> inline const char* str<double>(double){ return "double"; }
//template <> inline const char* str<void>(){ return "void"; }

template <> inline const char* str<int*>(int*){ return "int*"; }
template <> inline const char* str<unsigned int*>(unsigned int*){ return "unsigned int*"; }
template <> inline const char* str<short*>(short*){ return "short*"; }
template <> inline const char* str<unsigned short*>(unsigned short*){ return "unsigned short*"; }
template <> inline const char* str<char*>(char*){ return "char*"; }
template <> inline const char* str<unsigned char*>(unsigned char*){ return "unsigned char*"; }
template <> inline const char* str<long*>(long*){ return "long*"; }
template <> inline const char* str<float*>(float*){ return "float*"; }
template <> inline const char* str<double*>(double*){ return "double*"; }
template <> inline const char* str<void*>(void*){ return "void*"; }

//----------------------------------------------------------------------
template <> inline bool isNumber<int>(int){ return true; }
template <> inline bool isNumber<unsigned int>(unsigned int){ return true; }
template <> inline bool isNumber<char>(char){ return true; }
template <> inline bool isNumber<unsigned char>(unsigned char){ return true; }
template <> inline bool isNumber<short>(short){ return true; }
template <> inline bool isNumber<unsigned short>(unsigned short){ return true; }
template <> inline bool isNumber<long>(long){ return true; }
template <> inline bool isNumber<unsigned long>(unsigned long){ return true; }
template <> inline bool isNumber<float>(float){ return true; }
template <> inline bool isNumber<double>(double){ return true; }

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

}
/*

template < typename typeT >
struct type
{
	enum { sup = 0
	, inf = 0
	, nBits = sizeOf(typeT)<<3
	, isSigned = 0
	, isInteger = 0
	, isPointer = 0
	, staticTypeId = 0
	};
};

template <> struct type<int>
{
	enum { sup = INT_MAX
	, inf = INT_MIN
	, isSigned = 1
	, isInteger = 1
	, isPointer = 0
	, staticTypeId = 1
	};
};

template <> struct type<unsigned int>
{
	enum { sup = INT_MAX
	, inf = INT_MIN
	, isSigned = 1
	, isInteger = 1
	, isPointer = 0
	, staticTypeId = 1
	};
};

*/

#endif
