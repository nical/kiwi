
#ifndef KIWI_CORE_STATICACCESSPORT_DECL_HPP
#define KIWI_CORE_STATICACCESSPORT_DECL_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include "AbstractAccessPort.hpp"

#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/Tuple.hpp"
#include "kiwi/mpl/MakePointer.hpp"
#include "kiwi/mpl/AsTypeList.hpp"
#include "kiwi/mpl/TypeListTransform.hpp"

namespace kiwi{
namespace core{

struct AlwaysCompatiblePolicy{
  static bool isCompatible(const AbstractAccessPort& ap, const AbstractDataPort& dp){
    kiwi::out << "flag test " << ( ( dp.flag() & ap.flag() ) == ap.flag() ) << endl;
    return ( ( dp.flag() & ap.flag() ) == ap.flag() );
  }
};

template<typename TContainerTypeList, typename TCompatibilityPolicy, AccessFlag TAccessFlag>
class StaticAccessPort : public AbstractAccessPort {
public:
  typedef typename kiwi::mpl::AsTypeList<TContainerTypeList>::type ContainerTypeList;
  typedef TCompatibilityPolicy CompatibilityPolicy;
  static const AccessFlag Flag = TAccessFlag;
  AccessFlag flag() const { return Flag; }

  bool isCompatible( AbstractDataPort& port ) const {
    return CompatibilityPolicy::isCompatible( *this, port );
  }
  
protected:
  typedef typename kiwi::mpl::typelist::Transform<ContainerTypeList,kiwi::mpl::MakePointer_2>::type ContainerPtrTypeList;
  
  kiwi::mpl::Tuple<ContainerPtrTypeList> _toUpdate;
};



}//namespace
}//namespace


#endif
