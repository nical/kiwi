
#ifndef KIWI_MPL_TYPELIST_HPP
#define KIWI_MPL_TYPELIST_HPP
#pragma once

#include "kiwi/core/Commons.hpp"

#define KIWI_TYPELIST_MAX_SIZE 10

#define TypeList_1(T1) kiwi::mpl::TypeList<T1,kiwi::NullType>
#define TypeList_2(T1,T2) kiwi::mpl::TypeList<T1,TypeList_1(T2) > 
#define TypeList_3(T1,T2,T3) kiwi::mpl::TypeList<T1,TypeList_2(T2,T3) > 
#define TypeList_4(T1,T2,T3,T4) kiwi::mpl::TypeList<T1,TypeList_3(T2,T3,T4) > 
#define TypeList_5(T1,T2,T3,T4,T5) kiwi::mpl::TypeList<T1,TypeList_4(T2,T3,T4,T5) > 
#define TypeList_6(T1,T2,T3,T4,T5,T6) kiwi::mpl::TypeList<T1,TypeList_5(T2,T3,T4,T5,T6) > 
#define TypeList_7(T1,T2,T3,T4,T5,T6,T7) kiwi::mpl::TypeList<T1,TypeList_6(T2,T3,T4,T5,T6,T7) > 
#define TypeList_8(T1,T2,T3,T4,T5,T6,T7,T8) kiwi::mpl::TypeList<T1,TypeList_7(T2,T3,T4,T5,T6,T7,T8) > 
#define TypeList_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) kiwi::mpl::TypeList<T1,TypeList_8(T2,T3,T4,T5,T6,T7,T8,T9) > 
#define TypeList_10(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10) kiwi::mpl::TypeList<T1,TypeList_9(T2,T3,T4,T5,T6,T7,T8,T9,T10) > 

namespace kiwi{
namespace mpl{


template<class T1, class T2>
struct TypeList{
  typedef T1 type;
  typedef T2 tail;
  static const int size = T2::size+1;
};

template<class T1>
struct TypeList<T1, kiwi::NullType>{
  typedef T1 type;
  typedef NullType tail;
  static const int size = 1;
};


namespace typelist{

template<class typelist_, int i> struct at{ };
template<class typelist_> struct at<typelist_,0>{
  typedef typename typelist_::type type;};
template<class typelist_> struct at<typelist_,1>{
  typedef typename typelist_::tail::type type;};
template<class typelist_> struct at<typelist_,2>{
  typedef typename typelist_::tail::tail::type type;};
template<class typelist_> struct at<typelist_,3>{
  typedef typename typelist_::tail::tail::tail::type type;};
template<class typelist_> struct at<typelist_,4>{
  typedef typename typelist_::tail::tail::tail::tail::type type;};
template<class typelist_> struct at<typelist_,5>{
  typedef typename typelist_::tail::tail::tail::tail::tail::type type;};
template<class typelist_> struct at<typelist_,6>{
  typedef typename typelist_::tail::tail::tail::tail::tail::tail::type type;};
template<class typelist_> struct at<typelist_,7>{
  typedef typename typelist_::tail::tail::tail::tail::tail::tail::tail::type type;};
template<class typelist_> struct at<typelist_,8>{
  typedef typename typelist_::tail::tail::tail::tail::tail::tail::tail::type::type type;};
template<class typelist_> struct at<typelist_,9>{
  typedef typename typelist_::tail::tail::tail::tail::tail::tail::tail::type::type::type type;};

}//namespace typelist


}//namespace mpl
}//namespace kiwi




#endif
