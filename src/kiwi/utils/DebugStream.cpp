
#include "DebugStream.hpp"


namespace kiwi{
namespace utils{


DebugStream& DebugStream::error(){
    return *this;
}

DebugStream& DebugStream::endl(){
  (*_stream) << std::endl;
  _endl = true;
  return *this;
}


DebugStream& operator << (DebugStream& stream, EndOfLine& eol){
  return stream.endl(); 
}


void DebugStream::beginBlock(const kiwi::string& message){  
  *this << KIWI_BEGINBLOCK_1 << message << KIWI_BEGINBLOCK_2; endl();
  ++indentation;
}
void DebugStream::endBlock(const kiwi::string& message){
  --indentation;
  *this << KIWI_ENDBLOCK_1 << message << KIWI_ENDBLOCK_2; endl();
  
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



}//namespace
utils::DebugStream out(std::cout);
utils::EndOfLine endl;
}//namespace
