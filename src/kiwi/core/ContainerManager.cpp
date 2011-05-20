

#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/core/ContainerManager.hpp"
#include "kiwi/core/Container.hpp"

#include <vector>
#include <assert.h>
#include <string.h>

#define CM_CHECK_INIT assert(_init);

namespace kiwi{
namespace core{


ContainerInfo::ContainerInfo( const char* const name, kiwi::int32 parent)
: superClassUid(parent){
  SCOPEDBLOCK_MACRO("ContainerInfo::constructor")
  strncpy(uniqueName, name, KIWI_CONTAINER_NAME_MAX_LENGHT);
  out << uniqueName << endl;
}



ContainerManager::ContainerManager(){
   _containerInfo.push_back( ContainerInfo("AbstractContainer", 0 ) );
}

ContainerManager* ContainerManager::_instance = 0;
static bool _useAnotherManager = false;

ContainerManager* ContainerManager::create(ContainerManager* useAnotherManager){
  if(useAnotherManager)
    _instance = useAnotherManager;
  else
    _instance = new ContainerManager();
  return _instance;
}

bool ContainerManager::isCreated(){
  return _instance;
}

ContainerManager* ContainerManager::getInstance(){
  if(_instance){
    return _instance;
  }else{
    return create();
  }
}


ContainerInfo* ContainerManager::containerInfo(int32 id){
  return &_containerInfo[id];
}

int32 ContainerManager::classUid(const char* uniqueName){
  SCOPEDBLOCK_MACRO("ContainerManager::classUid")
  ContainerInfo* iter = &_containerInfo[0];
  for(kiwi::int32 i = 0; i < _containerInfo.size(); ++i){
    bool different = false;
    char* itName = iter->uniqueName;
    out << "comparing " << iter->uniqueName << " and " << uniqueName << endl;
    if(!strncmp(iter->uniqueName,uniqueName,KIWI_CONTAINER_NAME_MAX_LENGHT))
      return i;
    ++iter;
  }
  return -1;
}



}//namespace
}//namespace

#undef CM_CHECK_INIT





//ex of uniqueNames:
//
// generic::int32
// [proxy]generic::int8
// generic::vector_3_float
// generic::vector_3_int32
// image::RGBA32
// image::Chan8
// generic::array_2_int
// audio::MultiSampleBuffer
// gl::FrameBufferObject
// text::utf8Text


