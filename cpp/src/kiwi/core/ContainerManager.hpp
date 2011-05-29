#pragma once
#ifndef KIWI_CORE_CONTAINERMANAGER_HPP
#define KIWI_CORE_CONTAINERMANAGER_HPP

#include <vector>
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Container.hpp"

#define KIWI_CONTAINER_NAME_MAX_LENGHT 64
#define KIWI_MAX_SUBCONTAINERS 32

namespace kiwi{
namespace core{

typedef AbstractContainer* (*NewContainerFunction)(void);
typedef void (*DeleteContainerFunction)( AbstractContainer* );



struct ContainerInfo{
  char uniqueName[KIWI_CONTAINER_NAME_MAX_LENGHT];
  kiwi::int32 baseClassUid;
  std::vector<kiwi::int32> subContainerClassUid;
  NewContainerFunction newContainer;
  DeleteContainerFunction deleteContainer;

  //constructors
  ContainerInfo(){}
  ContainerInfo(
    const char* const name
    , kiwi::int32 baseUid
    , const std::vector<kiwi::int32>& subContainers
    , NewContainerFunction newC = 0
    , DeleteContainerFunction deleteC = 0 );
  ContainerInfo(
    const char* const name
    , kiwi::int32 baseUid ){}//TODO!!
  
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
    int32 baseClassUid = registerContainer<typename ContainerType::SuperClass>();
    int32 uid = classUid( ContainerType::className() );
    if(uid == -1){
      out << "ClassUid not found" << endl;
      _containerInfo.push_back( ContainerInfo( ContainerType::className()
        , baseClassUid ) );
      uid = _containerInfo.size()-1; 
      ContainerType::setUid( uid );
      //for(kiwi::int32 i = O; i < ContainerType::nbSubContainers()e; ++i){
      //  _containerInfo.subContainerClassUid.push_back()
      //}
    }else{ out << ContainerType::className() << " already registered"<<endl; }
    return uid;
  }
 
  kiwi::int32 nbRegisteredContainers() const {return _containerInfo.size();}  
  ContainerInfo* containerInfo(int32 id);
  int32 classUid(const char* uniqueName);

  bool isChildOf(kiwi::int32 baseClass, kiwi::int32 superClass) const;
private:  
  std::vector<ContainerInfo> _containerInfo;
  static ContainerManager* _instance;
};//ContainerManager



template<> kiwi::int32 ContainerManager::registerContainer<AbstractContainer>();




}//namespace
}//namespace


#endif
