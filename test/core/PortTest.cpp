
#include "kiwi/core/PortSystem.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include <assert.h>

using kiwi::out;
using kiwi::endl;

int main(){
  SCOPEDBLOCK_MACRO("core::Port::Test")

  kiwi::core::StaticDataPort<int,kiwi::core::READ_WRITE> dp;
 
  kiwi::core::StaticAccessPort<
    int
    ,kiwi::core::AlwaysCompatiblePolicy
    ,kiwi::core::READ_WRITE
  > ap;

  // ports are note connected yet
  assert( ! ap.isConnected() );
  assert( ! dp.isConnected() );

  //connecting should be fine
  assert( ap.connect( dp ) );
  out << "ap.flag: " << ap.flag() << endl; 
  out << "dp.flag: " << dp.flag() << endl; 

  // port should (at least) say that they're connected
  assert( ap.isConnected() );
  assert( dp.isConnected() );

  // check the link
  assert( ap.connectedPort() == &dp );

  // disconnecting from the access port
  ap.disconnect();
  assert( ! ap.isConnected() );
  assert( ! dp.isConnected() );

  //connecting should be fine again
  assert( ap.connect( dp ) );
  out.foo();
  // disconnecting from the data port
  dp.disconnect();
  out.bar();
  assert( ! ap.isConnected() );
  assert( ! dp.isConnected() );



}
