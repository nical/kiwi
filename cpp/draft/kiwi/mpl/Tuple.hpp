
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
  static const int size = typelist_::size;
  typedef typelist_ typelist;
  typedef Tuple<typename typelist_::tail> NestedTuple;
  
  type _obj;
  NestedTuple _next;
};
template<> struct Tuple<EmptyTypeList>{
  typedef NullType type;
  static const int size = 0;
  typedef EmptyTypeList typelist;
  typedef NullType NestedTuple; //not sure this is required

};

typedef Tuple<EmptyTypeList> EmptyTuple; 



namespace tuple{

/*
template<int i, class tuple_> struct randomAccess{
  typedef typename randomAccess<i-1,tuple_>::tuple::NestedTuple tuple;
  //typedef typename typelist::type type;
  static tuple& get(tuple_& t) { return t._next; }
};
template<class tuple_> struct randomAccess<0,tuple_>{
  typedef tuple_ tuple; 
  typedef typename tuple_::typelist typelist; 
  typedef typename typelist::type type; 
  static tuple& get(tuple_& t) {return t;}
};
*/
template<int i, class tuple_> struct randomAccess{};
template<class tuple_> struct randomAccess<0,tuple_>{
  typedef tuple_ tuple;
  static tuple& get(tuple_& t) { return t; }
};
template<class tuple_> struct randomAccess<1,tuple_>{
  typedef typename tuple_::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next; }
};
template<class tuple_> struct randomAccess<2,tuple_>{
  typedef typename tuple_::NestedTuple::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next._next; }
};
template<class tuple_> struct randomAccess<3,tuple_>{
  typedef typename tuple_::NestedTuple::NestedTuple::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next._next._next; }
};
template<class tuple_> struct randomAccess<4,tuple_>{
  typedef typename tuple_::NestedTuple::NestedTuple::NestedTuple::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next._next._next._next; }
};
template<class tuple_> struct randomAccess<5,tuple_>{
  typedef typename tuple_::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next._next._next._next._next; }
};
template<class tuple_> struct randomAccess<6,tuple_>{
  typedef typename tuple_::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next._next._next._next._next._next; }
};
template<class tuple_> struct randomAccess<7,tuple_>{
  typedef typename tuple_::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next._next._next._next._next._next._next; }
};
template<class tuple_> struct randomAccess<8,tuple_>{
  typedef typename tuple_::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next._next._next._next._next._next._next._next; }
};
template<class tuple_> struct randomAccess<9,tuple_>{
  typedef typename tuple_::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple::NestedTuple tuple;
  static tuple& get(tuple_& t) { return t._next._next._next._next._next._next._next._next._next; }
};


template<int i> struct at{
  template<class tuple_>
  static typename randomAccess<i,tuple_>::tuple::type&
    get(tuple_& t){ return randomAccess<i,tuple_>::get(t)._obj; }
};





/*
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
*/

}//namespace tuple


}//namespace mpl
}//namespace kiwi


#endif
