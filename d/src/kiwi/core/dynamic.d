module kiwi.core.dynamic;

import kiwi.core.commons;
import kiwi.core.interfaces;
import kiwi.core.data;



interface CompatibilityPolicy{
  bool isCompatible(PortInterface thisPort, PortInterface port);
}



//######################################################################
class Node : NodeInterface {

  override @property NodeListenerInterface listener(){
    return _listener;
  }
  override @property void listener(NodeListenerInterface listnr){
      _listener = listnr;
  }

private:
  NodeListenerInterface _listener;
}


//######################################################################
class Port : PortInterface{
  this(){
    mixin(logFunction!"dynamic.Port.constructor");
  }
  this(DataTypeInfo dataTypeInfo = null, CompatibilityPolicy compatibility = null){
    mixin(logFunction!"dynamic.Port.constructor");
    _dataTypeInfo = dataTypeInfo;
    _compatibility = compatibility;
  }

  public override bool isCompatible(PortInterface port){    
    mixin(logFunction!"dynamic.Port.isCompatible");
    if(_compatibility is null)
      return true;
    else
      return _compatibility.isCompatible(this,port);
  }

  public override bool isComposite(){
    mixin(logFunction!"DynamicPort.isComposite");
    if( _dataTypeInfo is null )
      return false;
    else
      return _dataTypeInfo.isComposite();    
  }

  public override bool disconnectAll(){
    mixin(logFunction!"DynamicPort.disconnectAll");
    while( connections.length > 0 ){
        disconnect(
    }
    return false;
    // TODO
  }

  protected override void doConnect(PortInterface toConnect){
    mixin(logFunction!"DynamicPort.doConnect");
    // verify that toConnect is not already connected.
    foreach( connectn ; connections ){
      if( connectn is toConnect ) return;
    }
    _connections ~= toConnect;
  }

  protected override void doDisconnect(PortInterface toConnect){
    mixin(logFunction!"DynamicPort.doDisconnect");
  }

  override @property DataInterface data(){
    return _data;
  }
  override @property DataTypeInfo type(){ return _dataTypeInfo; }
  override @property PortInterface[] connections(){ return _connections; }

  protected CompatibilityPolicy _compatibility;
  protected PortInterface[]     _connections;
  protected DataInterface       _data;
  protected DataTypeInfo        _dataTypeInfo;
}


// ---------------------------------------------------------------------


unittest{
  auto p1 = new kiwi.core.dynamic.Port();
  auto p2 = new kiwi.core.dynamic.Port();

  p1.connect(p2);
  
}

