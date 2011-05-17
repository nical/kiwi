#pragma once
#ifndef KIWI_CORE_CONTAINERMANAGER_HPP
#define KIWI_CORE_CONTAINERMANAGER_HPP

#include <vector>
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Container.hpp"


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
  char uniqueName[64];
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

  static ContainerManager* create(ContainerManager* useAnotherManager = 0);
  static void destroy();
  static bool isCreated();
  static ContainerManager* getInstance();

  typedef AbstractContainer* (*NewContainerFunction)(void);
  typedef void (*DeleteContainerFunction)( AbstractContainer* );

  template<typename ContainerType> kiwi::int32 registerContainer(){
    _containerInfo.push_back(ContainerInfo(
      ContainerType::className(), registerContainer<ContainerType::SuperClass>() )
    );
  }
 
    
  ContainerInfo* containerInfo(int32 id);
  int32 containerId(char* uniqueName);
  
private:  
  std::vector<ContainerInfo> _containerInfo;
  static ContainerManager* _instance;
};//ContainerManager



template<> kiwi::int32 ContainerManager::registerContainer<AbstractContainer>(){
    _containerInfo[0] = ContainerInfo("AbstractContainer", 0 );
  }




}//namespace
}//namespace


#endif
