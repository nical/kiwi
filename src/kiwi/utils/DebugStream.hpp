
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
#define SCOPEDBLOCK_MACRO(message) kiwi::utils::ScopedBlock kiwi_scop##__LINE__(message, kiwi::out);
#define FUNCTIONBLOCK_MACRO kiwi::utils::ScopedBlock kiwi_scop##__LINE__(__FUNC__, kiwi::out);
#else
#define SCOPEDBLOCK_MACRO(message) 
#define FUNCTIONBLOCK_MACRO   
#endif


namespace kiwi{
namespace utils{

class DebugStream{
public:
  DebugStream(std::ostream& stdStream){
    _stream = &stdStream;
    _endl = true;
    indentation = 0;
  }
  DebugStream& endl();
  DebugStream& error();
  DebugStream& foo() {
    (*this) << emphasePrefix() <<"foo" << resetFormat(); endl();
    return *this; }
  DebugStream& bar() {
    (*this) << emphasePrefix() <<"bar" << resetFormat(); endl();
    return *this; }
  DebugStream& plop(){
    (*this) << emphasePrefix() <<"plop" << resetFormat(); endl();
    return *this; }
  void beginBlock(const kiwi::string& message);
  void endBlock(const kiwi::string& message);
  
  template<typename T> DebugStream& operator << (const T& data){
    if(_endl){
      for(int i = 0; i < indentation; ++i)
        (*_stream) << KIWI_INDENTATION_PATTERN;
    }
    _endl = false;
    (*_stream) << data;
    return *this;
  }
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

private:
  bool _endl;
  std::ostream* _stream;
};

struct EndOfLine{
public:
  const char* text(){
    return "\n";
  }
};

DebugStream& operator << (DebugStream& stream, EndOfLine& eol);


class ScopedBlock{
public:
  ScopedBlock(const kiwi::string& message,DebugStream& stream){
    _stream = &stream;
    _msg = message;
    stream.beginBlock(message);
  }
  ~ScopedBlock(){
    _stream->endBlock(_msg);
  }
  
private:
  DebugStream* _stream;
  kiwi::string _msg;
};



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
\\033[0m reset; clears all colors and styles (to white on black)

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
