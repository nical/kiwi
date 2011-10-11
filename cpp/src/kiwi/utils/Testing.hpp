
#ifndef KIWI_UTILS_TESTING_HPP
#define KIWI_UTILS_TESTING_HPP
#pragma once

#include <assert.h>

static char const* kiwi_testname;

#define KIWI_TEST( label, expr ) kiwi::utils::TestManager::getInstance()->test(expr,label,__FILE__,__LINE__);
#define KIWI_TEST_assert( label, expr ) kiwi::utils::TestManager::getInstance()->test(expr,label,__FILE__,__LINE__);\
assert(expr);

#define KIWI_BEGIN_TESTING( testname ) kiwi::log << log.bold() << log.blue() << "[Begin test] " << log.reset() << testname << kiwi::endl;\
kiwi_testname = testname;\
log.indentation++;

#define KIWI_END_TESTING kiwi::utils::TestManager::getInstance()->testResult();

#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/DebugStream.hpp"

namespace kiwi{
namespace utils{

class TestManager{
public:
  TestManager(){
    _out = &kiwi::log;
    _success = 0;
    _successSinceLastError = 0;
  } 
  
  static TestManager* getInstance(){
    if(_instance){
      return _instance;
    }else{
      _instance = new TestManager;
      return _instance;
    }
  }

  bool test( bool expr
    , const char* const label
    , const char* const file
    , int line
  ){
      ++_nbTests;
      if(expr){
        if( _out->has(TEST_LEVEL(0) ) ){
        (*_out) << _out->blue() << "Test::" << _out->reset() <<line<<": "
          << _out->green() <<"passed successfully."
          << _out->reset() <<" ["<< label <<"]" ;
        _out->endl();
            if(_successSinceLastError % 20 == 0 && _successSinceLastError != 0)
            {
                (*_out) << "[!] " << _out->lightBlue() << "Achievement unlocked! "
                        << _out->yellow() << "\""<< _successSinceLastError <<" successful tests in a row\"\n"
                        << _out->reset();
            }
        }
        ++_success;
        ++_successSinceLastError;
        return true;
      }else{
        if( _out->has(TEST_LEVEL(0) ) ){
        (*_out) << _out->blue() << "Test::" << _out->reset() <<line<<": "
          << _out->red() <<"failed. | "<< label ;
        _out->endl();
        (*_out) << file << "  " << line;
        _out->endl();
        }
        return false;
      }
  }

  bool testResult(){
    if( _out->has(TEST_LEVEL(0) ) ){
    (*_out) << "\n" << "The Test terminated ";
    if( _success < _nbTests ) (*_out) << _out->red() << "with errors.\n" << _out->reset();
    else (*_out) << _out->green() << "without errors.\n" << _out->reset();
    (*_out) << _nbTests << " tests | "
      << _success << " success | ";
    if( _success < _nbTests ) (*_out) << _out->red();
    (*_out)  << _nbTests-_success << " errors.\n";

    (*_out) << _out->reset() << _out->bold() << _out->blue()
    << "[End test] " << _out->reset()
      << kiwi_testname << kiwi::endl << kiwi::endl;  
    log.indentation--;
    }
    return _success < _nbTests;
  }
  
protected:
  static TestManager* _instance;
  DebugStream* _out;
  int32 _nbTests;
  int32 _success;
  int32 _successSinceLastError;
};



}//namespace
}//namespace


#endif
