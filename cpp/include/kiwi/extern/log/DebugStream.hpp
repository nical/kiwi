
#ifndef KIWI_UTILS_DEBUGSTREAM_HPP
#define KIWI_UTILS_DEBUGSTREAM_HPP

#define USE_SCOPEDBLOCK_MACRO

#include <iostream>
#include "kiwi/core/Commons.hpp"

#define KIWI_INDENTATION_PATTERN "  "
#define KIWI_BEGINBLOCK_1 "\033[1;34m{Begin block} "
#define KIWI_BEGINBLOCK_2 " "
#define KIWI_ENDBLOCK_1 "\033[1;34m{End block} "
#define KIWI_ENDBLOCK_2 " "

#ifdef USE_SCOPEDBLOCK_MACRO
#define SCOPEDBLOCK(message) kiwi::utils::ScopedBlock kiwi_scop##__LINE__(message, kiwi::log, KIWI_DEBUG_3);
#define FUNCTIONBLOCK kiwi::utils::ScopedBlock kiwi_scop##__LINE__(__FUNCTION__, kiwi::log, KIWI_DEBUG_3);
#else
#define SCOPEDBLOCK(message) \

#define FUNCTIONBLOCK \

#endif

#define KIWI_BIT( n ) 1 << n

namespace kiwi{


// print targets
/*
enum{ None      = 0
    , All       = -1
    , Default   = KIWI_BIT(  0 )
    , TEST_0    = KIWI_BIT(  1 )
    , TEST_1    = KIWI_BIT(  2 )
    , TEST_2    = KIWI_BIT(  3 )
    , TEST_3    = KIWI_BIT(  4 )
    , TEST_4    = KIWI_BIT(  5 )
    , TEST_5    = KIWI_BIT(  6 )
    , DEBUG_0   = KIWI_BIT(  7 )
    , DEBUG_1   = KIWI_BIT(  8 )
    , DEBUG_2   = KIWI_BIT(  9 )
    , DEBUG_3   = KIWI_BIT( 10 )
    , DEBUG_4   = KIWI_BIT( 11 )
    , DEBUG_5   = KIWI_BIT( 12 )
    , WARNING_0 = KIWI_BIT( 13 )
    , WARNING_1 = KIWI_BIT( 14 )
    , WARNING_2 = KIWI_BIT( 15 )
    , WARNING_3 = KIWI_BIT( 16 )
    , WARNING_4 = KIWI_BIT( 17 )
    , WARNING_5 = KIWI_BIT( 18 )
    , INFO_0    = KIWI_BIT( 19 )
    , INFO_1    = KIWI_BIT( 20 )
    , INFO_2    = KIWI_BIT( 21 )
    , INFO_3    = KIWI_BIT( 22 )
    , INFO_4    = KIWI_BIT( 23 )
    , INFO_5    = KIWI_BIT( 24 )
    , ERROR     = KIWI_BIT( 25 )
    , TEST_ALL  = TEST_0|TEST_1|TEST_2|TEST_3|TEST_4|TEST_5 
    , INFO_ALL  = INFO_0|INFO_1|INFO_2|INFO_3|INFO_4|INFO_5 
    , DEBUG_ALL = DEBUG_0|DEBUG_1|DEBUG_2|DEBUG_3|DEBUG_4|DEBUG_5 
    , WARNING_ALL = WARNING_0|WARNING_1|WARNING_2|WARNING_3|WARNING_4|WARNING_5 
};
*/

#define KIWI_NONE       0
#define KIWI_ALL        -1
#define KIWI_DEFAULT    KIWI_BIT(  0 )
#define KIWI_TEST_0     KIWI_BIT(  1 )
#define KIWI_TEST_1     KIWI_BIT(  2 )
#define KIWI_TEST_2     KIWI_BIT(  3 )
#define KIWI_TEST_3     KIWI_BIT(  4 )
#define KIWI_TEST_4     KIWI_BIT(  5 )
#define KIWI_TEST_5     KIWI_BIT(  6 )
#define KIWI_DEBUG_0    KIWI_BIT(  7 )
#define KIWI_DEBUG_1    KIWI_BIT(  8 )
#define KIWI_DEBUG_2    KIWI_BIT(  9 )
#define KIWI_DEBUG_3    KIWI_BIT( 10 )
#define KIWI_DEBUG_4    KIWI_BIT( 11 )
#define KIWI_DEBUG_5    KIWI_BIT( 12 )
#define KIWI_WARNING_0  KIWI_BIT( 13 )
#define KIWI_WARNING_1  KIWI_BIT( 14 )
#define KIWI_WARNING_2  KIWI_BIT( 15 )
#define KIWI_WARNING_3  KIWI_BIT( 16 )
#define KIWI_WARNING_4  KIWI_BIT( 17 )
#define KIWI_WARNING_5  KIWI_BIT( 18 )
#define KIWI_INFO_0     KIWI_BIT( 19 )
#define KIWI_INFO_1     KIWI_BIT( 20 )
#define KIWI_INFO_2     KIWI_BIT( 21 )
#define KIWI_INFO_3     KIWI_BIT( 22 )
#define KIWI_INFO_4     KIWI_BIT( 23 )
#define KIWI_INFO_5     KIWI_BIT( 24 )
#define KIWI_ERROR      KIWI_BIT( 25 )
#define KIWI_TEST_ALL   KIWI_TEST_0|KIWI_TEST_1|KIWI_TEST_2|KIWI_TEST_3|KIWI_TEST_4|KIWI_TEST_5
#define KIWI_INFO_ALL   KIWI_INFO_0|KIWI_INFO_1|KIWI_INFO_2|KIWI_INFO_3|KIWI_INFO_4|KIWI_INFO_5
#define KIWI_DEBUG_ALL  KIWI_DEBUG_0|KIWI_DEBUG_1|KIWI_DEBUG_2|KIWI_DEBUG_3|KIWI_DEBUG_4|KIWI_DEBUG_5
#define KIWI_WARNING_ALL KIWI_WARNING_0|KIWI_WARNING_1|KIWI_WARNING_2|KIWI_WARNING_3|KIWI_WARNING_4|KIWI_WARNING_5


kiwi::int32 WARNING_LEVEL( kiwi::int32 n );
kiwi::int32 DEBUG_LEVEL( kiwi::int32 n );
kiwi::int32 TEST_LEVEL( kiwi::int32 n );  
kiwi::int32 INFO_LEVEL( kiwi::int32 n );   

namespace utils{

class DebugStream;


// -----------------------------------------------------------------------------

class DebugStream{
public:
  class ProxyStream;
  
  /**
   * Constructor;
   */ 
  DebugStream(std::ostream& stdStream, kiwi::int32 targets = KIWI_ALL){
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
  ProxyStream& warning(kiwi::int32 level= 3 );
  ProxyStream& debug( kiwi::int32 level = 3 );
  ProxyStream&  info( kiwi::int32 level = 3 );
  ProxyStream&  test( kiwi::int32 level = 3 );

  /**
   * Debug shortcut too print foo.
   */ 
  DebugStream& foo(kiwi::int32 targets = KIWI_DEBUG_5) {
    if(has(targets))
      (*this) << emphasePrefix() <<"foo" << resetFormat(); endl();
    return *this; }
  /**
   * Debug shortcut too print bat.
   */ 
  DebugStream& bar(kiwi::int32 targets = KIWI_DEBUG_5) {
    if(has(targets))
        (*this) << emphasePrefix() <<"bar" << resetFormat(); endl();
    return *this; }
  /**
   * Debug shortcut too print plop.
   */ 
  DebugStream& plop(kiwi::int32 targets = KIWI_DEBUG_5) {
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
    if(_targets){
      if(_endl){
        for(int i = 0; i < indentation; ++i)
          (*_stream) << KIWI_INDENTATION_PATTERN;
      }
      _endl = false;
      (*_stream) << data;
    }
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
  const char*  yellow();
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
    , kiwi::int32 targets = KIWI_ALL)
  {
    _stream = &stream;
    _msg = message;
    _targets = targets;
    if(_stream->has(kiwi::DEBUG_LEVEL(3)))
      _stream->beginBlock(_msg);
  }
  ~ScopedBlock(){
    if(_stream->has(kiwi::DEBUG_LEVEL(3)))
      _stream->endBlock(_msg);
  }
  
private:
  DebugStream* _stream;
  kiwi::string _msg;
  kiwi::int32 _targets;
};



DebugStream& operator << (DebugStream& stream, EndOfLine& eol);



}//namespace
extern utils::DebugStream log;
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
