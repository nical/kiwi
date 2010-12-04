
#include "ArgumentProcessor.hpp"

namespace kiwi
{

ArgumentProcessor::ArgumentProcessor(int argc, char** argv)
{
	_verbose = _remote = _process = _server= _invalid = false;
	_version =_help = FALSE;
	
	int state = GENERAL;
	
	
	
		
	
	for(unsigned i = 1; i < argc; ++i)
	{
		if(kiwi::string(argv[1]) == kiwi::string("--version") )
		{
			_version = state;
		}
		else if (kiwi::string(argv[1]) == kiwi::string("--help") )
		{
			_help = state;
		}
		else if(kiwi::string(argv[i]) == "-i" ) state = INPUT;
		else if(kiwi::string(argv[i]) == "-o" ) state = OUTPUT;
		else if(kiwi::string(argv[i]) == "-v" ) _verbose = true;
		else if(state == INPUT)
		{
			_inputs.push_back( kiwi::string(argv[i]) );
		}
		else if(state == OUTPUT)
		{
			_outputs.push_back( kiwi::string(argv[i]) );
		}
		else if(state == PROCESS)
		{
			_filterName = kiwi::string(argv[i]);
			state = GENERAL;
		}
		else if( (kiwi::string(argv[i]) == "process") && (state == GENERAL) )
		{
			_process = true;
			state = PROCESS;
		}
		else if( (kiwi::string(argv[i]) == "server") && (state == GENERAL) )
		{
			_server = true;
		}
		else if( (kiwi::string(argv[i]) == "remote") && (state == GENERAL) )
		{
			_remote = true;
		}
		
		
	}
	
	
	
}



}// namespace
