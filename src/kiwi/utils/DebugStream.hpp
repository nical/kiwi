
#ifndef KIWI_UTILS_DEBUGSTREAM_HPP
#define KIWI_UTILS_DEBUGSTREAM_HPP

#define USE_SCOPEDBLOCK_MACRO

#include <iostream>
#include "kiwi/core/Commons.hpp"

#define KIWI_INDENTATION_PATTERN "  "
#define KIWI_BEGINBLOCK_1 "[begin block] "
#define KIWI_BEGINBLOCK_2 " "
#define KIWI_ENDBLOCK_1 "[end block] "
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
  DebugStream& foo() { (*_stream) << "foo"; endl(); }
  DebugStream& bar() { (*_stream) << "bar"; endl(); }
  DebugStream& plop(){ (*_stream) << "plop"; endl(); }
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
protected:
  static const char*  infoPrefix();
  static const char*  errorPrefix();
  static const char*  warningPrefix();
  static const char*  emphasePrefix();
  static const char*  resetFormat();

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
