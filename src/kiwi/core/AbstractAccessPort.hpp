
#ifndef KIWI_CORE_ABSTRACTACCESSPORT_HPP
#define KIWI_CORE_ABSTRACTACCESSPORT_HPP
#pragma once



namespace kiwi{
namespace core{

// forward declarations
class AbstractDataPort;

typedef enum{ READ = 1, WRITE = 2, READ_WRITE = READ | WRITE } AccessFlag;

class AbstractAccessPort{
public:
  // constructor
  AbstractAccessPort()  : _connectedPort(0){  }

  // methods
  bool connect( AbstractDataPort& port );
  void disconnect();

  // virtual methods
  virtual AccessFlag flag() const { return READ; }
  virtual bool isCompatible( AbstractDataPort& port ) const = 0;
  
  // inline methods
  bool isConnected() const { return connectedPort() != 0; }
  AbstractDataPort* connectedPort() const { return _connectedPort; }


protected:
  
  // methods
  virtual void dataUpdated() {}

  // attributes
  AbstractDataPort* _connectedPort;
};


}//namespace
}//namespace


#endif
