
#ifndef KIWI_UTILS_ASSERT_HPP
#define KIWI_UTILS_ASSERT_HPP

#ifdef KIWI_USE_ASSERT
#include <assert.h>
#define kiwi_assert(expr) assert(expr)
#define kiwi_doc_assert(expr,doc) assert(expr)
#else
#define kiwi_assert(expr)  
#define kiwi_doc_assert(expr)  
#endif


/*
namespace kiwi{

void assert_failed(char const * expr, char const * function, char const * file, long line);

}
#ifdef KIWI_USE_ASSERT

#ifndef KIWI_ASSERT_EXIT
#include <assert.h>
#define kiwi_assert(expr) assert(expr); 
#else
#define kiwi_assert(expr) if(expr){} else assert_failed(#expr,__FUNC__,__FILE__,__LINE__);
#endif
#else
#define kiwi_assert(expr)  
#endif
*/

#endif
