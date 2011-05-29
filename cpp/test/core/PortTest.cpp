#define KIWI_TESTING

#include "kiwi/core/PortSystem.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include <assert.h>
#include "kiwi/utils/Testing.hpp"

using kiwi::out;
using kiwi::endl;

int main(int argc, char** argv){
  KIWI_BEGIN_TESTING("core::Port::Test")
  out.parseArgs(argc,argv);
  
  kiwi::core::StaticDataPort<int,kiwi::core::READ_WRITE> dp;
  kiwi::core::StaticDataPort<int,kiwi::core::READ> dp_read;
 
  kiwi::core::StaticAccessPort<
    int
    ,kiwi::core::AlwaysCompatiblePolicy
    ,kiwi::core::READ_WRITE
  > ap;

  
  KIWI_TEST( "The AccessPort should not be connected at this stage.","c.ps.01a",
    ! ap.isConnected()  );
  KIWI_TEST( "The DataPort should not be connected at this stage.","c.ps.01b",
    ! dp.isConnected()  );

  
  KIWI_TEST( "Connecting ([data R+W]>>[access R+W]) should work fine.","c.ps.02",
    ap.connect( dp ) );


  KIWI_TEST( "The AccessPort should be connected.","c.ps.03",
    ap.isConnected() );
  KIWI_TEST( "The DataPort should be connected.","c.ps.03",
    dp.isConnected() );

  // check the link
  KIWI_TEST( "Checking the AccessPort's connectedPort() pointer.","c.ps.04",
    ap.connectedPort() == &dp );

  // disconnecting from the access port
  ap.disconnect();
  
  KIWI_TEST( "The AccessPort should be disconnected.","c.ps.05a",
    ! ap.isConnected() );
  KIWI_TEST( "The DataPort should be disconnected.","c.ps.05a",
    ! dp.isConnected() );

  KIWI_TEST( "Reconnecting should work.","c.ps.06",
    ap.connect( dp ) );
    
  
  // disconnecting from the data port
  dp.disconnect();
  
  KIWI_TEST( "The AccessPort should not be connected.","c.ps.07a",
    ! ap.isConnected() );
  KIWI_TEST( "The AccessPort should not be connected.","c.ps.07b",
    ! dp.isConnected() );


  KIWI_TEST( "Connecting ([data R]>>[access R+W]) should not work work.","c.ps.08",
    ! ap.connect( dp_read ) );

  return KIWI_END_TESTING
}
