/**
 *@file types.hpp 
 *@brief A collection of template functions to retrieve inforrmations about the basic cpp scalar types.
 *@author Nicolas Silva
 */


#ifndef TYPES_HPP
#define TYPES_HPP

#include <limits.h>


/**
 * @namespace types
 * The namespace grouping the collection of functions to help with type manipulations in template implementations. 
 */
namespace types
{
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
 * @brief Returns true if the type passed as template parameter is integer
 */ 
template<typename T> inline bool isPointer(T var = 0){ return true; }

/**
 * @brief Returns a string containing the name of the template type
 */ 
template<typename T> inline const char* str(T var = 0){ return "unknown type"; }


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
