
#include "kiwi/mpl/Tuple.hpp"
#include "kiwi/mpl/DynamicTupleWrapper.hpp"
#include "kiwi/mpl/TupleApplyFunctor.hpp"
#include <assert.h>


using namespace kiwi;

typedef kiwi::mpl::Tuple<TypeList_0> Tuple_0;

typedef TypeList_6(kiwi::int32_t,kiwi::int32_t,kiwi::int32_t,kiwi::int32_t,kiwi::int32_t,kiwi::int32_t) TList6i;
typedef kiwi::mpl::Tuple<TList6i> Tuple6i;

typedef TypeList_6(kiwi::int8_t,kiwi::int8_t,kiwi::int8_t,kiwi::int8_t,kiwi::int8_t,kiwi::int8_t) TList6c;
typedef kiwi::mpl::Tuple<TList6c> Tuple6c;

typedef TypeList_6(kiwi::int8_t,kiwi::int32_t,kiwi::int8_t,kiwi::int32_t,kiwi::int8_t,kiwi::int32_t) TList3ci;
typedef kiwi::mpl::Tuple<TList3ci> Tuple3ci;

typedef TypeList_6(kiwi::int8_t,kiwi::int32_t,float,double,kiwi::uint8_t,float) TList_cifdsf;
typedef kiwi::mpl::Tuple<TList_cifdsf> Tuple_cifdsf;


struct M{ kiwi::int32_t val; M(kiwi::int32_t v):val(v){} };
struct A : public M{ A():M(42){} };
struct B : public M{ B():M(12){} };
struct C : public M{ C():M(1234){} };
struct D : public M{ D():M(1337){} };
typedef TypeList_4(A,B,C,D) TList_abc;
typedef kiwi::mpl::Tuple<TList_abc> Tuple_abc;

template<class Tuple_t>
void TupleIntegralTypeTest(){
  Tuple_t myTuple;
  
  mpl::tuple::at<0>::get(myTuple) = 0;
  mpl::tuple::at<1>::get(myTuple) = 1;
  mpl::tuple::at<2>::get(myTuple) = 2;
  mpl::tuple::at<3>::get(myTuple) = 3;
  mpl::tuple::at<4>::get(myTuple) = 4;
  mpl::tuple::at<5>::get(myTuple) = 5;

  assert(mpl::tuple::at<0>::get(myTuple) == 0);
  assert(mpl::tuple::at<1>::get(myTuple) == 1);
  assert(mpl::tuple::at<2>::get(myTuple) == 2);
  assert(mpl::tuple::at<3>::get(myTuple) == 3);
  assert(mpl::tuple::at<4>::get(myTuple) == 4);
  assert(mpl::tuple::at<5>::get(myTuple) == 5);
  
  Tuple_t sameTuple = myTuple;

  assert(mpl::tuple::at<0>::get(sameTuple) == 0);
  assert(mpl::tuple::at<1>::get(sameTuple) == 1);
  assert(mpl::tuple::at<2>::get(sameTuple) == 2);
  assert(mpl::tuple::at<3>::get(sameTuple) == 3);
  assert(mpl::tuple::at<4>::get(sameTuple) == 4);
  assert(mpl::tuple::at<5>::get(sameTuple) == 5);


}


int main(){
ScopedBlockMacro("Tuple::Test")

/*  
  Debug::print() << "sizeof Tuple6i: " << sizeof(Tuple6i) << "\n";
  Debug::print() << "sizeof Tuple6c: " << sizeof(Tuple6c) << "\n";
  Debug::print() << "sizeof Tuple3ci: " << sizeof(Tuple3ci) << "\n";
*/
  DumpValueMacro( sizeof(Tuple6i) )
  DumpValueMacro( sizeof(Tuple6c) )
  DumpValueMacro( sizeof(Tuple3ci) )

  TupleIntegralTypeTest<Tuple6i>();
  TupleIntegralTypeTest<Tuple6c>();
  TupleIntegralTypeTest<Tuple3ci>();
  TupleIntegralTypeTest<Tuple_cifdsf>();

  Tuple_0 emptyTuple;

  Tuple_abc tupleabc;
  
  M* hli[4];
  kiwi::mpl::DynamicTupleWrapper::exec(emptyTuple, hli);
  kiwi::mpl::DynamicTupleWrapper::exec(tupleabc, hli);
  assert( hli[0]->val == 42 );
  assert( hli[1]->val == 12 );
  assert( hli[2]->val == 1234 );

  
  
return 0;
}
