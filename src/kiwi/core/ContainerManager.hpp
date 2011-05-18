#pragma once
#ifndef KIWI_CORE_CONTAINERMANAGER_HPP
#define KIWI_CORE_CONTAINERMANAGER_HPP

#include <vector>
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Container.hpp"

#define KIWI_CONTAINER_NAME_MAX_LENGHT 64

namespace kiwi{
namespace core{

typedef AbstractContainer* (*NewContainerFunction)(void);
typedef void (*DeleteContainerFunction)( AbstractContainer* );

template<typename T> AbstractContainer defaultNewContainer(){
  return new T;
};
template<typename T> void defaultDeleteContainer(T*& instance){
  delete instance;
  instance = 0;
};

struct ContainerInfo{
  char uniqueName[KIWI_CONTAINER_NAME_MAX_LENGHT];
//  NewContainerFunction newContainer;
//  DeleteContainerFunction deleteContainer;
  kiwi::int32 parentUid;
  //constructors
  ContainerInfo(){}
  ContainerInfo(
    const char* const name
//    , NewContainerFunction nc
//  , DeleteContainerFunction dc
    , kiwi::int32 parent)
 : parentUid(parent){
    for(kiwi::uint32 i = 0; i < 64; ++i){
      if((i > 1) && (name[i-2] == '\\') && (name[i-1] == '0')) break;
      uniqueName[i] = name[i];
    }
  }
};

class AbstractContainer;

class ContainerManager{
public:
  ContainerManager();

  static ContainerManager* create(ContainerManager* useAnotherManager = 0);
  static void destroy();
  static bool isCreated();
  static ContainerManager* getInstance();

  typedef AbstractContainer* (*NewContainerFunction)(void);
  typedef void (*DeleteContainerFunction)( AbstractContainer* );

  template<typename ContainerType> kiwi::int32 registerContainer(){
    SCOPEDBLOCK_MACRO("ContainerManager::registerContainer")
    int32 parentUid = registerContainer<typename ContainerType::SuperClass>();
    int32 uid = classUid( ContainerType::className() );
    if(uid == -1){
      _containerInfo.push_back( ContainerInfo( ContainerType::className()
        , parentUid ) );
      ContainerType::setUid( _containerInfo.size() );
      uid = _containerInfo.size()-1;
    }
    return uid;
  }
 
    
  ContainerInfo* containerInfo(int32 id);
  int32 classUid(const char* uniqueName);
  
private:  
  std::vector<ContainerInfo> _containerInfo;
  static ContainerManager* _instance;
};//ContainerManager



template<> kiwi::int32 ContainerManager::registerContainer<AbstractContainer>(){
  SCOPEDBLOCK_MACRO("ContainerManager::registerContainer(AbstactContainer)")
  return 0;
}




}//namespace
}//namespace


#endif
