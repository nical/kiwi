#define KIWI_USE_ASSERT

#include "kiwi/core/AbstractDataPort.hpp"
#include "kiwi/core/StaticDataPort_decl.hpp"
#include "kiwi/core/AbstractAccessPort.hpp"
#include "kiwi/core/StaticAccessPort_decl.hpp"

#include "kiwi/utils/assert.hpp"
#include "kiwi/core/Container.hpp"
#include "core/DumbContainer.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/mpl/TypeListTransform.hpp"
#include "kiwi/mpl/SameType.hpp"
#include "kiwi/mpl/TypeListPrint.hpp"
#include "kiwi/mpl/TypeToStr.hpp"
#include "kiwi/mpl/AsTypeList.hpp"

#include "kiwi/mpl/IsRelated.hpp"

#include <typeinfo>



template<typename T> struct MakePointer{ typedef T* type; };
  



using kiwi::out;
using kiwi::endl;

void tempTest();

int main(){
  ScopedBlockMacro("kiwi v2::test")
  out.beginBlock("kiwi v2::test");
  
  IntContainer ic;
  Vector3iContainer vect3i(42,1337,12);

  out.beginBlock("subContainer tests");
  kiwi_assert( vect3i.subContainer<0>().value() == 42  );
  kiwi_assert( vect3i.subContainer<1>().value() == 1337);
  kiwi_assert( vect3i.subContainer<2>().value() == 12  );
  Vector3iContainer::subContainerInfo<0>::type& subc0 = vect3i.subContainer<0>();
  out.endBlock("subContainer tests");
  

  out.beginBlock("output indentation tests");
  out << "hello" << endl;
  out.beginBlock("foo");
  out << "indent" << " test" << endl << "foo" << endl;
  out.endBlock("foo");
  out.indentation++;
  out << "indent test" << endl << "foo" << endl;
  out.indentation-=2;
  out.endBlock("output indentation tests");
  

  out.beginBlock("mpl tests");

  typedef kiwi::mpl::typelist::Transform<TypeList_3(int,float,char), MakePointer>::type TransformedTypeList;

  out << "TypeToStr: " << kiwi::mpl::type<int>::str() << endl;
  out << "TypeToStr: " << kiwi::mpl::type<char>::str() << endl;
  out << "TypeToStr: " << kiwi::mpl::type<float*>::str() << endl;

  out << "foo" <<endl;
  kiwi::mpl::typelist::print<TypeList_3(int*,float*,char*)>::in(out);
  out << endl << "bar" <<endl;
  bool transformTest = kiwi::mpl::SameType<
    TypeList_3(int*,float*,char*)
    , TransformedTypeList
  >::value;
 kiwi::mpl::typelist::print<TransformedTypeList>::in(out);
 out.endl();
  kiwi_assert(transformTest);
  out.endBlock("mpl tests");
  

  kiwi::core::StaticDataPort<int,kiwi::core::READ_WRITE> dp;
 
  kiwi::core::StaticAccessPort<int,kiwi::core::AlwaysCompatiblePolicy,kiwi::core::READ_WRITE> ap;

  assert( ap.connect( dp ) );
  out << "ap.flag: " << ap.flag() << endl; 
  out << "dp.flag: " << dp.flag() << endl; 
  
  out << "end of the test" << endl;
  
  int isrelatedtest  = kiwi::mpl::IsRelated<kiwi::core::AbstractAccessPort,int>::value;
  int isrelatedtest2 = kiwi::mpl::IsRelated<
    kiwi::core::AbstractAccessPort,
    kiwi::core::StaticAccessPort<int,kiwi::core::AlwaysCompatiblePolicy,kiwi::core::READ_WRITE>
  >::value;
   
  assert(!isrelatedtest);
  assert(isrelatedtest2);
  
}



void tempTest(){

}
