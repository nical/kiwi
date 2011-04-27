#define KIWI_USE_ASSERT


#include "kiwi/utils/assert.hpp"
#include "kiwi/core/Container.hpp"
#include "core/DumbContainer.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/mpl/TypeListTransform.hpp"
#include "kiwi/mpl/SameType.hpp"
#include "kiwi/mpl/TypeListPrint.hpp"
#include "kiwi/mpl/TypeToStr.hpp"
#include "kiwi/mpl/AsTypeList.hpp"



template<typename T> struct MakePointer{ typedef T* type; };
  


using kiwi::out;
using kiwi::endl;


int main(){
  ScopedBlockMacro("kiwi v2::test")
  out.beginBlock("kiwi v2::test");
  
 
  

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
  




  out << "end of the test" << endl;

}

