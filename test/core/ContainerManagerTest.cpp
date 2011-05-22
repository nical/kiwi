
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/ContainerManager.hpp"


using kiwi::out;
using kiwi::endl;

using namespace kiwi::core;
using namespace kiwi;


class DummyContainer1 : public AbstractContainer{
KIWI_CONTAINER_UID_MACRO
KIWI_CONTAINER_NAME_MACRO(DummyContainer1)
public:
  typedef AbstractContainer SuperClass;
  int val;
};
class DummyContainer2 : public DummyContainer1{
KIWI_CONTAINER_UID_MACRO
KIWI_CONTAINER_NAME_MACRO(DummyContainer2)
public:
  typedef DummyContainer1 SuperClass;
  int val;
};
class DummyContainer4 : public DummyContainer2{
KIWI_CONTAINER_UID_MACRO
KIWI_CONTAINER_NAME_MACRO(DummyContainer4)
public:
  typedef DummyContainer2 SuperClass;
  int val;
};
class DummyContainer3 : public AbstractContainer{
KIWI_CONTAINER_UID_MACRO
KIWI_CONTAINER_NAME_MACRO(DummyContainer3)
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

  KIWI_TEST( "The ContainerManager should be created now.","c.cm.03",
    ContainerManager::isCreated()  );
  
  KIWI_TEST( "Checking ContainerManager::getInstance pointer.","c.cm.04",
     cm == ContainerManager::getInstance()  );

  int32 dc4 = cm->registerContainer<DummyContainer4>();
  int32 dc1 = cm->registerContainer<DummyContainer1>();
  int32 dc2 = cm->registerContainer<DummyContainer2>();
  int32 dc3 = cm->registerContainer<DummyContainer3>();


  KIWI_TEST( "checking ContainerManager::getUid on container 1","c.cm.05a",
     cm->classUid("DummyContainer1") == dc1  );
  KIWI_TEST( "checking ContainerManager::getUid on container 2","c.cm.05b",
     cm->classUid("DummyContainer2") == dc2  );
  KIWI_TEST( "checking ContainerManager::getUid on container 3","c.cm.05c",
     cm->classUid("DummyContainer3") == dc3  );
  KIWI_TEST( "checking ContainerManager::getUid on container 4","c.cm.05d",
     cm->classUid("DummyContainer4") == dc4  );
  KIWI_TEST( "checking ContainerManager::getUid with an invalid name","c.cm.05e",
     cm->classUid("invalid") == -1  );

  // true
  bool testParent1 = cm->isChildOf(
    cm->classUid("DummyContainer2")
    ,cm->classUid("AbstractContainer"));
  //true
  bool testParent2 = cm->isChildOf(
    cm->classUid("DummyContainer2")
    ,cm->classUid("DummyContainer1"));
  // in the wrong order: should return false
  bool testParent3 = ! cm->isChildOf(
    cm->classUid("DummyContainer1")
    ,cm->classUid("DummyContainer2"));
  // true  
  bool testParent4 = cm->isChildOf(
    cm->classUid("DummyContainer4")
    ,cm->classUid("DummyContainer1"));

  KIWI_TEST( "isChildOf: with AbstractContainer as super class (true for any base class)", "c.cm.06a", testParent1 )
  KIWI_TEST( "isChildOf: with direct relationship (true)", "c.cm.06b"
    , testParent2 )
  KIWI_TEST( "isChildOf: argument in the wrong order (false)", "c.cm.06c"
    , testParent3 )
  KIWI_TEST( "isChildOf: with indirect relationship (true)", "c.cm.06d"
    , testParent4 )

  out << "containerInfo[0]: " << cm->containerInfo(0)->uniqueName << endl
      << "containerInfo[1]: " << cm->containerInfo(1)->uniqueName << endl
      << "containerInfo[2]: " << cm->containerInfo(2)->uniqueName << endl
      << "containerInfo[3]: " << cm->containerInfo(3)->uniqueName << endl
      << "containerInfo[4]: " << cm->containerInfo(4)->uniqueName << endl
      << "nb registered containers: " << cm->nbRegisteredContainers();


  return KIWI_END_TESTING
}
