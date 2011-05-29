
#ifndef KIWI_CORE_CONTAINER_HPP
#define KIWI_CORE_CONTAINER_HPP

#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/Tuple.hpp"


//------------------------------------------------------------------------------
#define KIWI_CONTAINER_UID_MACRO \
friend class kiwi::core::ContainerManager; \
protected: \
static kiwi::int32& _class_uid_() { static kiwi::int32 uid = 0; return uid;} \
static void setUid(kiwi::int32 id) {_class_uid_() = id;} \
public: \
static kiwi::int32 getUid() { return _class_uid_(); } \
kiwi::int32 getClassUid() const { return _class_uid_(); }
//------------------------------------------------------------------------------
#define KIWI_CONTAINER_NAME_MACRO( name ) public: static const char* className() {return #name ;} 

namespace kiwi{
namespace core{

class ContainerManager;

/**
 * Abstract mother class for containers.
 *
 */ 
class AbstractContainer{
public:
  virtual ~AbstractContainer(){}
  virtual int32 getClassUid() { return 0; }
};

/**
 * The class that implements the composite container's mecanism.
 *
 * Custom containers should inherit this class;
 */ 
template<typename TSubContainers>
class CompositeContainer : public AbstractContainer{
public:
  typedef TSubContainers SubContainersTypeList;
  enum { NbSubContainers = SubContainersTypeList::size };
  template<int i>
  struct subContainerInfo{
    typedef typename kiwi::mpl::typelist::at<SubContainersTypeList,i>::type type;
  };
  template<int i>
  typename kiwi::mpl::typelist::at<SubContainersTypeList,i>::type&
  subContainer(){
    return kiwi::mpl::tuple::at<i>::get(_subContainers);
  }
  
protected:
  typedef kiwi::mpl::Tuple<TSubContainers> SubContainerTuple;
  SubContainerTuple _subContainers;
};

typedef CompositeContainer<kiwi::mpl::EmptyTypeList> Container;

template<typename TValueType>
struct ContainerWrapper : public Container{
  typedef TValueType ValueType;
  enum { NbSubContainers = 0 };
  typedef mpl::EmptyTypeList SubContainersTypeList;
  
  ValueType data;
};


}//namespace
}//namespace


#endif

/*
class RGBA32Image:public Container{
  SUBCONTAINER(ColorChannel,_r,READ_WRITE)
  SUBCONTAINER(ColorChannel,_g,READ_WRITE)
  SUBCONTAINER(ColorChannel,_b,READ_WRITE)
  SUBCONTAINER(IntContainer,_width,READ)
  SUBCONTAINER(IntContainer,_height,READ)
public:
  void init(kiwi::int32 w,kiwi::int32 h){
    _data.resize(w*h);
    _width.init(w);
    _height.init(h);
    _r.init(this,0);
    _g.init(this,1);
    _b.init(this,2);
  }
protected:
  std::vector<kiwi::uint8> _data;
};
SUBCONTAINER_OUTLINE_MACRO(RGBA32Image,ColorChannel,_r,READ_WRITE)
SUBCONTAINER_NUMBER(3)
*/
/*
SUBCONTAINER(ctype,name,flag)
protected: ctype name;
public:   

*/
