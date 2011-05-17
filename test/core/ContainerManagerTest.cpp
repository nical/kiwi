
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/ContainerManager.hpp"


using kiwi::out;
using kiwi::endl;

using namespace kiwi::core;


class DummyContainer1 : public AbstractContainer{
KIWI_CONTAINER_UID_MACRO
public:
  typedef AbstractContainer SuperClass;
  int val;
};
class DummyContainer2 : public DummyContainer1{
KIWI_CONTAINER_UID_MACRO
public:
  typedef DummyContainer1 SuperClass;
  int val;
};
class DummyContainer3 : public AbstractContainer{
KIWI_CONTAINER_UID_MACRO
public:
  typedef AbstractContainer SuperClass;
  int val;
};


int main(){
  KIWI_BEGIN_TESTING("core::ContainerManager")

  KIWI_TEST( "The ContainerManager should not be created yet.","c.cm.01",
    ! ContainerManager::isCreated()  );

  ContainerManager* cm = ContainerManager::create();
    
  KIWI_TEST( "Creating the singleton.","c.cm.02", cm );
  KIWI_TEST( "checking ContainerManager::getInstance pointer.","c.cm.03",
     cm == ContainerManager::getInstance()  );


  

  return KIWI_END_TESTING
}
