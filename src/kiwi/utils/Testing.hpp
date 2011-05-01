
#ifndef KIWI_UTILS_TESTING_HPP
#define KIWI_UTILS_TESTING_HPP
#pragma once

#include <assert.h>

#ifdef KIWI_TESTING
#define kiwi_test( label, id, expr ) kiwi::utils::TestManager::getInstance()->test(expr,label,__FILE__,__LINE__,id);
#define kiwi_test_assert( label, id, expr ) kiwi::utils::TestManager::getInstance()->test(expr,label,__FILE__,__LINE__,id);\
assert(expr);
#else
#define kiwi_test( label, id, expr )
#define kiwi_test_assert( label, id, expr )  
#endif

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
    , const char* label
    , const char* file
    , int line
    , const char* id){
      ++_nbTests;
      if(expr){
        (*_out) << "Test::"<<id<<": passed successfully. ["<< label <<"]" ;
        _out->endl();
        ++_success;
        return true;
      }else{
        (*_out) << "Test::"<<id<<": failed. | "<< label ;
        _out->endl();
        (*_out) << file << "  " << line;
        _out->endl();
        return false;
      }
  }

  bool testResult(){
    (*_out) << "\n" << "The Test terminated ";
    if( _success < _nbTests ) (*_out) << "with errors.\n";
    else (*_out) << "without errors.\n";
    (*_out) << _nbTests << " tests | "
      << _success << " success | "
      << _nbTests-_success << " errors.\n";

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
