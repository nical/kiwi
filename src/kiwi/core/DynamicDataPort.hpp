#ifndef KIWI_CORE_DYNAMICDATAPORT_HPP
#define KIWI_CORE_DYNAMICDATAPORT_HPP


namespace kiwi{
namespace core{

class AbstractContainerInfo{
public:
  virtual kiwi::int32 nbSubContainers() const = 0;
  virtual ContainerInfo* parentContainerInfo() const = 0;
};
template<typename TContainerType>
class ContainerInfo : public AbstractContainerInfo{
  
};


class DynamicDataPort : AbstractDataPort{
public:
  DynamicDataPort(AbstractContainerInfo* ch = 0);
  bool setContainerInfo(AbstractContainerInfo* ch);
  
protected:
  AbstractContainer* _container;
  AbstractContainerHandler* _containerInfo;
  std::vector<DynamicDataPort*> _subPorts;
  DynamicDataPort* _motherPort;
};




}//namespace
}//namespace



#endif
