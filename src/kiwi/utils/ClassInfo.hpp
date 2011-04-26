
#pragma once
#ifndef KIWI_UTILS_CLASSINFO_HPP
#define KIWI_UTILS_CLASSINFO_HPP


namespace kiwi{
namespace utils{


struct ClassInfo
{
  ClassInfo( ClassInfo* parent )
  :_parent(parent){}
  
  bool isChildOf(ClassInfo* cInfo){
    if(_parent){
      if(cInfo == _parent) return true;
      else return _parent->isChildOf( cInfo );
    }else{
      return false;
    }
  }
  
private :
  ClassInfo* _parent;
};





}//namespace  
}//namespace  

template<class T> struct GetClassInfo{
  static kiwi::utils::ClassInfo* get() { return 0; }
};



#endif
