
#ifndef KIWI_UTILS_DEBUGSTREAM_HPP
#define KIWI_UTILS_DEBUGSTREAM_HPP

#define USE_SCOPEDBLOCK_MACRO

#include <iostream>
#include "kiwi/core/Commons.hpp"

#define KIWI_INDENTATION_PATTERN "  "
#define KIWI_BEGINBLOCK_1 "\033[1;30m[begin block] "
#define KIWI_BEGINBLOCK_2 " "
#define KIWI_ENDBLOCK_1 "\033[1;30m[end block] "
#define KIWI_ENDBLOCK_2 " "


#ifdef USE_SCOPEDBLOCK_MACRO
#define SCOPEDBLOCK_MACRO(message) kiwi::utils::ScopedBlock kiwi_scop##__LINE__(message, kiwi::out, kiwi::Debug);
#define FUNCTIONBLOCK_MACRO kiwi::utils::ScopedBlock kiwi_scop##__LINE__(__FUNCTION__, kiwi::out, kiwi::Debug);
#else
#define SCOPEDBLOCK_MACRO(message) 
#define FUNCTIONBLOCK_MACRO   
#endif


namespace kiwi{
  
// print targets 
enum{ None = 0, All = -1, Default = 1, Debug = 2, Test=4, Warning = 16, Error = 32
    , Lv0 = 64, Lv1 = 128, Lv2 = 256
    , Lv3 = 512, Lv4 = 1024, Lv5 = 2048  };

namespace utils{

class DebugStream;


// -----------------------------------------------------------------------------

class DebugStream{
public:
  class ProxyStream;
  
  /**
   * Constructor;
   */ 
  DebugStream(std::ostream& stdStream, kiwi::int32 targets = kiwi::All){
    _stream = &stdStream;
    _endl = true;
    indentation = 0;
    _targets = targets;
  }

  void parseArgs(int argc, char** argv);
  
  /**
   * Returns true if the stream has at least one of the targets
   */ 
  bool has(kiwi::int32 targets)const{
    return(targets & _targets);
  }
  /**
   * Set the print targets;
   */ 
  void setTargets(kiwi::int32 targets){ _targets = targets; }
  /**
   * Returns the print targets.
   */ 
  kiwi::int32 targets()const{ return _targets; }

  /**
   * End of line.
   */ 
  DebugStream& endl();
  ProxyStream& error();
  ProxyStream& warning();

  /**
   * Debug shortcut too print foo.
   */ 
  DebugStream& foo(kiwi::int32 targets = Debug) {
    if(has(targets))
      (*this) << emphasePrefix() <<"foo" << resetFormat(); endl();
    return *this; }
  /**
   * Debug shortcut too print bat.
   */ 
  DebugStream& bar(kiwi::int32 targets = Debug) {
    if(has(targets))
        (*this) << emphasePrefix() <<"bar" << resetFormat(); endl();
    return *this; }
  /**
   * Debug shortcut too print plop.
   */ 
  DebugStream& plop(kiwi::int32 targets = Debug) {
    if(has(targets))
        (*this) << emphasePrefix() <<"plop" << resetFormat(); endl();
    return *this; }
  /**
   * Begins an indentation block.
   */ 
  void beginBlock(const kiwi::string& message);
  /**
   * Ends an indentation block.
   */
  void endBlock(const kiwi::string& message);

  /**
   * Stream operator.
   */
  template<typename T> DebugStream& operator << (const T& data){
    if(_endl){
      for(int i = 0; i < indentation; ++i)
        (*_stream) << KIWI_INDENTATION_PATTERN;
    }
    _endl = false;
    (*_stream) << data;
    return *this;
  }
  /**
   * Public indentation property; 
   */ 
  int indentation;

  static const char*  infoPrefix();
  static const char*  errorPrefix();
  static const char*  warningPrefix();
  static const char*  emphasePrefix();
  static const char*  resetFormat();
  const char*  blue();
  const char*  red();
  const char*  green();
  const char*  purple();
  const char*  darkGray();
  const char*  lightBlue();
  const char*  lightGreen();
  const char*  lightRed();
  
  const char*  bold();
  const char*  italic();
  const char*  underlined();
  const char*  reset();

  /**
   * Proxy class that filters certain targets.
   */
  class ProxyStream{
  public:
    ProxyStream(){} //unsafe, do not use
    void setup(kiwi::int32 target, DebugStream* stream){
      _targets = target;
      _stream = stream;
    }
    template<typename T> ProxyStream& operator << (T& data){
      if( _stream->has(_targets) ) (*_stream) << data;
      return *this;
    }
  private:
    kiwi::int32 _targets;
    DebugStream* _stream;
  };
  /**
   * Returns a proxy using the targets passed in parameter.
   */ 
  ProxyStream& operator[](kiwi::int32 targets){
    _proxy.setup(targets,this);
    return _proxy;
  }

private:
  bool _endl;
  std::ostream* _stream;
  kiwi::int32 _targets;
  ProxyStream _proxy;
};

struct EndOfLine{
public:
  const char* text(){
    return "\n";
  }
};

DebugStream& operator << (DebugStream& stream, EndOfLine& eol);

// -----------------------------------------------------------------------------
class ScopedBlock{
public:
  ScopedBlock(const kiwi::string& message,DebugStream& stream
    , kiwi::int32 targets = kiwi::All )
  {
    _stream = &stream;
    _msg = message;
    _targets = targets;
    stream.beginBlock(message);
  }
  ~ScopedBlock(){
    _stream->endBlock(_msg);
  }
  
private:
  DebugStream* _stream;
  kiwi::string _msg;
  kiwi::int32 _targets;
};



DebugStream& operator << (DebugStream& stream, EndOfLine& eol);



}//namespace
extern utils::DebugStream out;
extern utils::EndOfLine endl;
}//namespace



#endif




/*
\\033[30m set foreground color to black

\\033[31m set foreground color to red

\\033[32m set foreground color to green

\\033[33m set foreground color to yellow

\\033[34m set foreground color to blue

\\033[35m set foreground color to magenta (purple)

\\033[36m set foreground color to cyan

\\033[37m set foreground color to white

\\033[40m set background color to black

\\033[41m set background color to red

\\033[42m set background color to green

\\033[43m set background color to yellow

\\033[44m set background color to blue

\\033[45m set background color to magenta (purple)

\\033[46m set background color to cyan

\\033[47m set background color to white

\\033[1;30m set foreground color to dark gray

\\033[1;31m set foreground color to light red

\\033[1;32m set foreground color to light green

\\033[1;33m set foreground color to yellow

\\033[1;34m set foreground color to light blue

\\033[1;35m set foreground color to light magenta (purple)

\\033[1;36m set foreground color to light cyan

\\033[1;37m set foreground color to white

\\033[1;40m set background color to dark gray

\\033[1;41m set background color to light red

\\033[1;42m set background color to light green

\\033[1;43m set background color to yellow

\\033[1;44m set background color to light blue

\\033[1;45m set background color to light magenta (purple)

\\033[1;46m set background color to light cyan

\\033[1;47m set background color to white

For other features:
\\033[0m reset; clears  colors and styles (to white on black)

\\033[1m bold on

\\033[3m italics on

\\033[4m underline on

\\033[5m blink on

\\033[7m reverse video on

\\033[8m nondisplayed (invisible)

\\033[x;yH moves cursor to line x, column y

\\033[xA moves cursor up x lines

\\033[xB moves cursor down x lines

\\033[xC moves cursor right x spaces

\\033[xD moves cursor left x spaces

\\033[2J clear screen and home cursor
*/
