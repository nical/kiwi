#include "kiwi/core/DynamicDataPort.hpp"
#include "kiwi/core/DynamicAccessPort.hpp"
#include "kiwi/utils/Testing.hpp"



using kiwi::out;
using kiwi::endl;
using namespace kiwi;
using namespace kiwi::core;


// -----------------------------------------------------------------------------
// declaring some container classes ...
class A : public AbstractContainer{
KIWI_CONTAINER_UID_MACRO
KIWI_CONTAINER_NAME_MACRO(A)
public:
  typedef AbstractContainer SuperClass;
};

class B : public AbstractContainer{
KIWI_CONTAINER_UID_MACRO
KIWI_CONTAINER_NAME_MACRO(A)
public:
  typedef AbstractContainer SuperClass;
};

class AA : public A{
KIWI_CONTAINER_UID_MACRO
KIWI_CONTAINER_NAME_MACRO(AA)
public:
  typedef A SuperClass;
};

// -----------------------------------------------------------------------------

int main(int argc, char** argv){
  KIWI_BEGIN_TESTING("core::DynamicPort::Test")
  out.parseArgs(argc,argv);

  DynamicDataPort dpA(ContainerManager::getInstance()->classUid("A"));
  DynamicDataPort dpB(ContainerManager::getInstance()->classUid("B"));
  DynamicDataPort dpAA(ContainerManager::getInstance()->classUid("AA"));
  DynamicDataPort dp0(); // container type: AbstractContainer (universal port);

  return KIWI_END_TESTING
}
