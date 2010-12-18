#include "TelnetRequestParser.hpp"

using namespace std;

namespace kiwi
{
  /**
   * Constructor.
   */
  TelnetRequestParser::TelnetRequestParser()
  {
    _continue=true;
  }

  /**
   * Parse a request, return a reply.
   */
  kiwi::string TelnetRequestParser::reply(kiwi::string request)
  {
    if (request=="help")
    {
      _reply="Help ! I need somebody. Help !";
      //kiwi::Happy::print(_reply);
    }
    else if ((request=="quit")||(request=="exit"))
    {
      _reply="Goodbye.";
      _continue=false;
    }
    else if (request!="")
    {
      _reply = "Command \"" + request +"\" not supported yet.\r\n"; 
    }
    return _reply;
  }
}
