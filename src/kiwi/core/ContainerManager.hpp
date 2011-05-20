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



struct ContainerInfo{
  char uniqueName[KIWI_CONTAINER_NAME_MAX_LENGHT];
//  NewContainerFunction newContainer;
//  DeleteContainerFunction deleteContainer;
  kiwi::int32 superClassUid;
  //constructors
  ContainerInfo(){}
  ContainerInfo(const char* const name, kiwi::int32 superUid);
  
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
    int32 superClassUid = registerContainer<typename ContainerType::SuperClass>();
    int32 uid = classUid( ContainerType::className() );
    if(uid == -1){
      out << "ClassUid not found" << endl;
      _containerInfo.push_back( ContainerInfo( ContainerType::className()
        , superClassUid ) );
      uid = _containerInfo.size()-1; 
      ContainerType::setUid( uid ); // TODO !
    }else{ out << ContainerType::className() << " already registered"<<endl; }
    return uid;
  }
 
  kiwi::int32 nbRegisteredContainers() const {return _containerInfo.size();}  
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
