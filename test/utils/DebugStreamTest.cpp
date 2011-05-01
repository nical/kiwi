#include "kiwi/utils/DebugStream.hpp"

using kiwi::out;
using kiwi::endl;

int main(){
  SCOPEDBLOCK_MACRO("DebugStream::Test")

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
  return 0;

}
