
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/utils/Testing.hpp"

using kiwi::out;
using kiwi::endl;

int main(int argc, char** argv){
  KIWI_BEGIN_TESTING("mpl::Tuple")
  out.parseArgs(argc,argv);
  
  return KIWI_END_TESTING
}
