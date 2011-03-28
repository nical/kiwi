
#ifndef KIWI_MPL_TUPLE_HPP
#define KIWI_MPL_TUPLE_HPP
#pragma once

#include "kiwi/core/Commons.hpp"
#include "kiwi/mpl/TypeList.hpp"

#define KIWI_TUPLE_MAX_SIZE 10


namespace kiwi{
namespace mpl{


template<class typelist_>
struct Tuple{
  typedef typename typelist_::type type;
  typedef typelist_ typelist;
  type _obj;
  Tuple<typename typelist_::tail> _next;
};
template<class lastType> struct Tuple< TypeList<lastType,NullType> >{
  typedef lastType type;
  typedef TypeList<lastType,NullType> typelist;
  lastType _obj;
};





namespace tuple{

template<class tuple_, int i> struct at{ };
template<class tuple_> struct at<tuple_,0>{
  typedef typename tuple_::typelist::type type;
  static type& get(tuple_& t) {return t._obj;}
};
template<class tuple_> struct at<tuple_,1>{
  typedef typename tuple_::typelist::tail::type type;
  static type& get(tuple_& t) {return t._next._obj;}
};
template<class tuple_> struct at<tuple_,2>{
  typedef typename tuple_::typelist::tail::tail::type type;
  static type& get(tuple_& t) {return t._next._next._obj;}
};
template<class tuple_> struct at<tuple_,3>{
  typedef typename tuple_::typelist::tail::tail::tail::type type;
  static type& get(tuple_& t) {return t._next._next._next._obj;}
};
template<class tuple_> struct at<tuple_,4>{
  typedef typename tuple_::typelist::tail::tail::tail::tail::type type;
  static type& get(tuple_& t) {return t._next._next._next._next._obj;}
};
template<class tuple_> struct at<tuple_,5>{
  typedef typename tuple_::typelist::tail::tail::tail::tail::tail::type type;
  static type& get(tuple_& t) {return t._next._next._next._next._next._obj;}
};
template<class tuple_> struct at<tuple_,6>{
  typedef typename tuple_::typelist::tail::tail::tail::tail::tail::tail::type type;
  static type& get(tuple_& t) {return t._next._next._next._next._next._next._obj;}
};
template<class tuple_> struct at<tuple_,7>{
  typedef typename tuple_::typelist::tail::tail::tail::tail::tail::tail::tail::type type;
  static type& get(tuple_& t) {return t._next._next._next._next._next._next._next._obj;}
};
template<class tuple_> struct at<tuple_,8>{
  typedef typename tuple_::typelist::tail::tail::tail::tail::tail::tail::type type;
  static type& get(tuple_& t) {return t._next._next._next._next._next._next._next._next._obj;}
};
template<class tuple_> struct at<tuple_,9>{
  typedef typename tuple_::typelist::tail::tail::tail::tail::tail::tail::type::type type;
  static type& get(tuple_& t) {return t._next._next._next._next._next._next._next._next._next._obj;}
};


}//namespace tuple


}//namespace mpl
}//namespace kiwi


#endif
