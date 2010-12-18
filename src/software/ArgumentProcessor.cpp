#include "ArgumentProcessor.hpp"

namespace kiwi
{
  //BEGIN : Constructor
  ArgumentProcessor::ArgumentProcessor(int argc, char** argv)
  {

    //BEGIN : Initialization
    _verbose = _remote = _process = _server= _invalid = false;
    _version =_help = FALSE;
    int state = GENERAL;
    //END: Initialization


    //BEGIN : Analytic loop
    for(unsigned i = 1; i < argc; ++i)
    {

      //Version
      if(kiwi::string(argv[1]) == kiwi::string("--version") )
      {
        _version = state;
      }

      //Help
      else if (kiwi::string(argv[1]) == kiwi::string("--help") )
      {
        _help = state;
      }

      //State changement (input, output, verbose)
      else if(kiwi::string(argv[i]) == "-i" ) state = INPUT;
      else if(kiwi::string(argv[i]) == "-o" ) state = OUTPUT;
      else if(kiwi::string(argv[i]) == "-v" ) _verbose = true;
      
      //Input state : Store argument in the input list
      else if(state == INPUT)
      {
        _inputs.push_back( kiwi::string(argv[i]) );
      }

      //Output state : Store argument in the output list
      else if(state == OUTPUT)
      {
        _outputs.push_back( kiwi::string(argv[i]) );
      }

      //Process state : Get filtername
      else if(state == PROCESS)
      {
        _filterName = kiwi::string(argv[i]);
        state = GENERAL;
      }

      //Server state : get port
      else if(state == SERVER)
      {
        _server = true;
        _port = atoi(argv[i]);
        state=GENERAL;
      }

      //State changement (process)
      else if( (kiwi::string(argv[i]) == "process") && (state == GENERAL) )
      {
        _process = true;
        state = PROCESS;
      }

      //State changement (server)
      else if( (kiwi::string(argv[i]) == "server") && (state == GENERAL) )
      {
        state = SERVER;
      }

      //State changement (remote)
      else if( (kiwi::string(argv[i]) == "remote") && (state == GENERAL) )
      {
        _remote = true;
      }
    }
    //END : Analytic loop
  }
  //END : Constructor
  

  int ArgumentProcessor::getServerPort()
  {
    if (_server) return _port;
    return 0;
  }

}
//END : Namespace
