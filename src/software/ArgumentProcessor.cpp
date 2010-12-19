// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



#include "ArgumentProcessor.hpp"

namespace kiwi{
  namespace app{


    ArgumentProcessor::ArgumentProcessor(const ArgumentProcessor& toCopy)
    {
      _verbose = toCopy._verbose;
      _version = toCopy._version;
      _invalid = toCopy._invalid;
      _process = toCopy._process;
      _server = toCopy._server;
      _remote = toCopy._remote;
      _port = toCopy._port;
      _help = toCopy._help;
      _filterName = toCopy._filterName;
      _inputs = toCopy._inputs;
      _outputs = toCopy._outputs;
    }

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




  }//namespace
}//namespace
