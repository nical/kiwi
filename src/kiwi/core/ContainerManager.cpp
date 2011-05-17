

#include "kiwi/core/ContainerManager.hpp"
#include "kiwi/core/Container.hpp"

#include <vector>
#include <assert.h>

#define CM_CHECK_INIT assert(_init);

namespace kiwi{
namespace core{



ContainerManager* ContainerManager::_instance = 0;
static bool _useAnotherManager = false;

ContainerManager* ContainerManager::create(ContainerManager* useAnotherManager){
  if(useAnotherManager)
    _instance = useAnotherManager;
  else
    _instance = new ContainerManager();
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


