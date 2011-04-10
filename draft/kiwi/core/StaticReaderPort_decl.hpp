

namespace kiwi{
namespace core{

template<typename TContainerTypeList, typename TCompatibilityPolicy>
class StaticReaderPort{
public:
  typedef kiwi::mpl::AsList<TContainerTypeList>::type ContainerTypeList;
  typedef TCompatibilityPolicy CompatibilityPolicy;
  
  
protected:
  typedef kiwi::mpl::typelist::Transform<ContainerTypeList,kiwi::mpl::MakePointer> ContainerPtrTypeList;
  
  kiwi::mpl::tuple::<ContainerPtrTypeList> _toUpdate;
};



}//namespace
}//namespace
