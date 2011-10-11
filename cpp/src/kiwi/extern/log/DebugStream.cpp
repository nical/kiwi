
#include "kiwi/utils/DebugStream.hpp"
#include <string.h>

namespace kiwi{

kiwi::int32 DEBUG_LEVEL( kiwi::int32 n )  { return KIWI_DEBUG_0   << (n<5?n:5); }
kiwi::int32 WARNING_LEVEL( kiwi::int32 n ){ return KIWI_WARNING_0 << (n<5?n:5); }
kiwi::int32 TEST_LEVEL( kiwi::int32 n )   { return KIWI_TEST_0    << (n<5?n:5); }
kiwi::int32 INFO_LEVEL( kiwi::int32 n )   { return KIWI_INFO_0    << (n<5?n:5); }

namespace utils{


DebugStream::ProxyStream& DebugStream::error(){
  if( has(KIWI_ERROR) )
    (*this) << errorPrefix();
  return (*this)[KIWI_ERROR];
}

DebugStream::ProxyStream& DebugStream::warning(int32 level){
  // why the hell isn't that syntax supported?!
  //return ((*this)[kiwi::Warning]) << errorPrefix();
  if( has(kiwi::WARNING_LEVEL(level)) )
    (*this) << errorPrefix();
  return (*this)[kiwi::WARNING_LEVEL(level)];
}

DebugStream::ProxyStream& DebugStream::debug(int32 level){
  return (*this)[kiwi::DEBUG_LEVEL(level)];
}
DebugStream::ProxyStream& DebugStream::test(int32 level){
  if( has(kiwi::TEST_LEVEL(level)) )
    (*this) << lightBlue();
  return (*this)[kiwi::TEST_LEVEL(level)];
}
DebugStream::ProxyStream& DebugStream::info(int32 level){
  if( has(kiwi::INFO_LEVEL(level)) )
    (*this) << blue();
  return (*this)[kiwi::INFO_LEVEL(level)];
}

DebugStream& DebugStream::endl(){
  if(_targets){
    (*_stream) << resetFormat() << std::endl;
    _endl = true;
  }
  return *this;
}


DebugStream& operator << (DebugStream& stream, EndOfLine& eol){
  return stream.endl(); 
}


void DebugStream::beginBlock(const kiwi::string& message){
  if(has(kiwi::DEBUG_LEVEL(3))){
    *this << emphasePrefix() << KIWI_BEGINBLOCK_1 << resetFormat()
      << message
      << emphasePrefix() << KIWI_BEGINBLOCK_2  << resetFormat();
    endl();
  }
  ++indentation;
}

void DebugStream::endBlock(const kiwi::string& message){
	--indentation;
	if(has(kiwi::DEBUG_LEVEL(3))){
		*this << emphasePrefix() << KIWI_ENDBLOCK_1 << resetFormat()
			<< message
			<< emphasePrefix() << KIWI_ENDBLOCK_2 << resetFormat();
		endl();
	}
}

const char*  DebugStream::infoPrefix()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[0m";
#else
  return "";
#endif
}
const char*  DebugStream::errorPrefix()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[0m\033[31m";
#else
  return "";
#endif
}

const char*  DebugStream::warningPrefix()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[0m\033[35m";
#else
  return "";
#endif
}

const char*  DebugStream::emphasePrefix()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[0m\033[1m";
#else
  return "";
#endif
}

const char*  DebugStream::resetFormat()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[0m";
#else
  return "";
#endif
}


const char*  DebugStream::reset()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[0m";
#else
  return "";
#endif
}

const char*  DebugStream::blue()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[34m";
#else
  return "";
#endif
}

const char*  DebugStream::red()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[31m";
#else
  return "";
#endif
}

const char*  DebugStream::green()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[32m";
#else
  return "";
#endif
}

const char*  DebugStream::yellow()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[33m";
#else
  return "";
#endif
}
const char*  DebugStream::lightGreen()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[1;32m";
#else
  return "";
#endif
}
const char*  DebugStream::lightBlue()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[1;34m";
#else
  return "";
#endif
}
const char*  DebugStream::purple()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[1;35m";
#else
  return "";
#endif
}
const char*  DebugStream::lightRed()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[1;31m";
#else
  return "";
#endif
}
const char*  DebugStream::darkGray()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[1;30m";
#else
  return "";
#endif
}

const char*  DebugStream::underlined()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[4m";
#else
  return "";
#endif
}

const char*  DebugStream::italic()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[3m";
#else
  return "";
#endif
}

const char*  DebugStream::bold()
{
#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
  return "\033[1m";
#else
  return "";
#endif
}

void DebugStream::parseArgs(int argc, char** argv){
  bool printOption = false;
  _targets = 0;
  for(kiwi::int32 i = 1; i < argc; ++i){
    if(printOption){
      if( argv[i][0] == '-' ) { return; }
      if(!strcmp(argv[i],      "None"      )){ _targets  = KIWI_NONE;     }
      else if(!strcmp(argv[i], "All"       )){ _targets  = KIWI_ALL;      }
      else if(!strcmp(argv[i], "Default"   )){ _targets |= KIWI_DEFAULT;  }
      else if(!strcmp(argv[i], "TEST_0"    )){ _targets |= KIWI_TEST_0;   }
      else if(!strcmp(argv[i], "TEST_1"    )){ _targets |= KIWI_TEST_1;   }
      else if(!strcmp(argv[i], "TEST_2"    )){ _targets |= KIWI_TEST_2;   }
      else if(!strcmp(argv[i], "TEST_3"    )){ _targets |= KIWI_TEST_3;   }
      else if(!strcmp(argv[i], "TEST_4"    )){ _targets |= KIWI_TEST_4;   }
      else if(!strcmp(argv[i], "TEST_5"    )){ _targets |= KIWI_TEST_5;   }
      else if(!strcmp(argv[i], "DEBUG_0"   )){ _targets |= KIWI_DEBUG_0;  }
      else if(!strcmp(argv[i], "DEBUG_1"   )){ _targets |= KIWI_DEBUG_1;  }
      else if(!strcmp(argv[i], "DEBUG_2"   )){ _targets |= KIWI_DEBUG_2;  }
      else if(!strcmp(argv[i], "DEBUG_3"   )){ _targets |= KIWI_DEBUG_3;  }
      else if(!strcmp(argv[i], "DEBUG_4"   )){ _targets |= KIWI_DEBUG_4;  }
      else if(!strcmp(argv[i], "DEBUG_5"   )){ _targets |= KIWI_DEBUG_5;  }
      else if(!strcmp(argv[i], "WARNING_0" )){ _targets |= KIWI_WARNING_0;}
      else if(!strcmp(argv[i], "WARNING_1" )){ _targets |= KIWI_WARNING_1;}
      else if(!strcmp(argv[i], "WARNING_2" )){ _targets |= KIWI_WARNING_2;}
      else if(!strcmp(argv[i], "WARNING_3" )){ _targets |= KIWI_WARNING_3;}
      else if(!strcmp(argv[i], "WARNING_4" )){ _targets |= KIWI_WARNING_4;}
      else if(!strcmp(argv[i], "WARNING_5" )){ _targets |= KIWI_WARNING_5;}
      else if(!strcmp(argv[i], "INFO_0"    )){ _targets |= KIWI_INFO_0;   }
      else if(!strcmp(argv[i], "INFO_1"    )){ _targets |= KIWI_INFO_1;   }
      else if(!strcmp(argv[i], "INFO_2"    )){ _targets |= KIWI_INFO_2;   }
      else if(!strcmp(argv[i], "INFO_3"    )){ _targets |= KIWI_INFO_3;   }
      else if(!strcmp(argv[i], "INFO_4"    )){ _targets |= KIWI_INFO_4;   }
      else if(!strcmp(argv[i], "INFO_5"    )){ _targets |= KIWI_INFO_5;   }
      else if(!strcmp(argv[i], "ERROR"     )){ _targets |= KIWI_ERROR;    }
      else if(!strcmp(argv[i], "INFO_ALL"  )){ _targets |= KIWI_INFO_ALL; }
      else if(!strcmp(argv[i], "TEST_ALL"  )){ _targets |= KIWI_TEST_ALL; }
      else if(!strcmp(argv[i], "DEBUG_ALL" )){ _targets |= KIWI_DEBUG_ALL;}
      else if(!strcmp(argv[i],"WARNING_ALL")){ _targets |= KIWI_WARNING_ALL;}
    }else if(!strcmp(argv[i], "-v"        )){ printOption = true; }
  }
  if(!printOption) _targets = KIWI_ALL;
}


}//namespace
utils::DebugStream log(std::cout);
utils::EndOfLine endl;
}//namespace
