
#ifndef KIWI_MPL_ISRELATED
#define KIWI_MPL_ISRELATED

namespace kiwi{
namespace mpl{

template<typename BaseT, typename DerivedT>
inline bool isRelated(const DerivedT&)
{
    DerivedT derived();
    char test(const BaseT&); // sizeof(test()) == sizeof(char)
    char (&test(...))[2];    // sizeof(test()) == sizeof(char[2])
    struct conversion 
    { 
        enum { exists = (sizeof(test(derived())) == sizeof(char)) }; 
    };
    return conversion::exists;
} 

template<typename BaseT, typename DerivedT>
struct IsRelated{
  static DerivedT derived();
  static char test(const BaseT&); // sizeof(test()) == sizeof(char)
  static char (&test(...))[2];    // sizeof(test()) == sizeof(char[2])
  enum{ value = (sizeof(test(derived())) == sizeof(char)) }; 
};


}//namespace
}//namespace

#endif
