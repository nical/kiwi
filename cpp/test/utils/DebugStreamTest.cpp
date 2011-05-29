#include "kiwi/utils/DebugStream.hpp"

using kiwi::out;
using kiwi::endl;

int main(int argc, char** argv){
  SCOPEDBLOCK_MACRO("DebugStream::Test")
  out.parseArgs(argc,argv);
  
  out.beginBlock("> a block");
  
    out.beginBlock("output indentation tests");
      out << "hello" << endl;
      out.beginBlock("foo");
        out << "indent" << " test" << endl << "foo" << endl;
      out.endBlock("foo");

      out.indentation++;
      out << "indent test (indentation ++)" << endl << "foo" << endl;
      out.indentation--;
      
      out.indentation-=2;
        out << "indent -= 2" << endl;
      out.indentation+=2;

    out.endBlock("output indentation tests");
  
  out.endBlock("< a block");

  out << out.red() << "red "
    << out.blue() << "blue "
    << out.green() << "green "
    << out.lightRed() << "lightRed "
    << out.lightBlue() << "lightBlue "
    << out.lightGreen() << "lightGreen "
    << out.darkGray() << "darkGray "
    << out.reset() << "normal "
    << out.underlined() << "underlined "
    << endl;


  out.parseArgs(argc, argv);
  
  int target = 1;
  for( kiwi::int32 i = 0; i < 8; ++ i){
    out[kiwi::All] << "--- "; 
    out[target] << "target test "<< target;
    out << endl;
    target *= 2;
  }

  out.test() << "test tagrget only" << endl;
  out.info() << "info tagrget only" << endl;
  out.debug() << "debug tagrget only" << endl;
  out.warning() << "warning tagrget only" << endl;

  return 0;

}
