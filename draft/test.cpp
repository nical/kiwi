#define KIWI_USE_ASSERT

#include "kiwi/utils/assert.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/core/DummyContainer.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/mpl/TypeListTransform.hpp"
#include "kiwi/mpl/SameType.hpp"
#include "kiwi/mpl/TypeListPrint.hpp"
#include "kiwi/mpl/TypeToStr.hpp"
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
  out.indentation++;
  out << "indent" << " test" << endl << "foo" << endl;
  out.indentation++;
  out << "indent test" << endl << "foo" << endl;
  out.indentation-=2;
  out.endBlock("output indentatkiwiion tests");

  out.beginBlock("mpl tests");

  typedef kiwi::mpl::typelist::Transform<TypeList_3(int,float,char), MakePointer>::type TransformedTypeList;

  out << " TypeToStr: " << kiwi::mpl::type<int>::str() << endl;
  out << " TypeToStr: " << kiwi::mpl::type<char>::str() << endl;
  out << " TypeToStr: " << kiwi::mpl::type<float*>::str() << endl;

  out << "foo" <<endl;
  kiwi::mpl::typelist::print<TypeList_3(int*,float*,char*)>::in(out);
  out << "\nbar" <<endl;
  bool transformTest = kiwi::mpl::SameType<
    TypeList_3(int*,float*,char*)
    , TransformedTypeList
  >::value;
 kiwi::mpl::typelist::print<TransformedTypeList>::in(out);
 out.endl();
  kiwi_assert(transformTest);
  out.endBlock("mpl tests");
  


  
  out << "end of the test" << endl;
}



void tempTest(){

}
