#include "kiwi/utils/DebugStream.hpp"

using kiwi::out;
using kiwi::endl;

int main(){
  ScopedBlockMacro("DebugStream::Test")

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

  return 0;

}
