
#ifndef KIWI_UTILS_TESTING_HPP
#define KIWI_UTILS_TESTING_HPP
#pragma once

#include <assert.h>

static char const* kiwi_testname;

#define KIWI_TEST( label, id, expr ) kiwi::utils::TestManager::getInstance()->test(expr,label,__FILE__,__LINE__,id);
#define KIWI_TEST_assert( label, id, expr ) kiwi::utils::TestManager::getInstance()->test(expr,label,__FILE__,__LINE__,id);\
assert(expr);

#define KIWI_BEGIN_TESTING( testname ) if(kiwi::out.has(kiwi::TEST_0)) kiwi::out << out.bold() << out.blue() << "[Begin test] " << out.reset() << testname << kiwi::endl;\
kiwi_testname = testname;\
out.indentation++;

#define KIWI_END_TESTING kiwi::utils::TestManager::getInstance()->testResult();

#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/DebugStream.hpp"

namespace kiwi{
namespace utils{

class TestManager{
public:
  TestManager(){
    _out = &kiwi::out;
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
    , const char* const id){
      ++_nbTests;
      if(expr){
        if( _out->has(TEST_LEVEL(0) ) ){
        (*_out) << _out->blue() << "Test::" << _out->reset() <<id<<": "
          << _out->green() <<"passed successfully."
          << _out->reset() <<" ["<< label <<"]" ;
        _out->endl();
        }
        ++_success;
        return true;
      }else{
        if( _out->has(TEST_LEVEL(0) ) ){
        (*_out) << _out->blue() << "Test::" << _out->reset() <<id<<": "
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
    out.indentation--;
    }
    return _success < _nbTests;
  }
  
protected:
  static TestManager* _instance;
  DebugStream* _out;
  int32 _nbTests;
  int32 _success;
};



}//namespace
}//namespace


#endif
