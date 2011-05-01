
#include "DebugStream.hpp"


namespace kiwi{
namespace utils{


DebugStream& DebugStream::error(){
  (*this) << errorPrefix();  
  return *this;
}

DebugStream& DebugStream::endl(){
  (*_stream) << resetFormat() << std::endl;
  _endl = true;
  return *this;
}


DebugStream& operator << (DebugStream& stream, EndOfLine& eol){
  return stream.endl(); 
}


void DebugStream::beginBlock(const kiwi::string& message){  
  *this << emphasePrefix() << KIWI_BEGINBLOCK_1 << resetFormat()
    << message
    << emphasePrefix() << KIWI_BEGINBLOCK_2  << resetFormat();
  endl();
  ++indentation;
}
void DebugStream::endBlock(const kiwi::string& message){
  --indentation;
  *this << emphasePrefix() << KIWI_ENDBLOCK_1 << resetFormat()
    << message
    << emphasePrefix() << KIWI_ENDBLOCK_2 << resetFormat();
  endl();
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



}//namespace
utils::DebugStream out(std::cout);
utils::EndOfLine endl;
}//namespace
