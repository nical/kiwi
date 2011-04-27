
#include "AbstractAccessPort.hpp"
#include "kiwi/utils/DebugStream.hpp"

namespace kiwi{
namespace core{



bool AbstractAccessPort::connect(AbstractDataPort& port ){
  ScopedBlockMacro("AbstractAccessPort::connect");
  return isCompatible(port);
}


}//namespace
}//namespace
