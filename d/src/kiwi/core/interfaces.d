module kiwi.core.interfaces;

import kiwi.core.commons;
import kiwi.core.data;

alias bool delegate(PortInterface,PortInterface) PortCompatibilityPolicy;

interface PortInterface{

  // ------------------------------------------------------- implemented
  final bool connect(PortInterface toConnect)
    in
    { 
        assert(!(toConnect is null),"Forbidden null parameter."); 
    }
    body
    {    
        mixin(logFunction!"Port.connect");
        if( isCompatible(toConnect) && toConnect.isCompatible(this) ){
          this.doConnect(toConnect);
          toConnect.doConnect(this);
          return true;
        }
        log.writeWarning(4,"uncompatible ports");
        if(!(node is null )) node.notifyPortConnected(this, toConnect);
        return false;
    }
  
  final bool disconnect(PortInterface toDisconnect)
    in
    {
      assert(!(toDisconnect is null),"Forbidden null parameter.");
    }
    body
    {
      mixin(logFunction!"Port.disconnect");
      
      if( !isConnectedTo(toDisconnect) ) 
        return false;
      
      foreach( port ; connections ){
        if( port is toDisconnect ){
            port.doDisconnect( this );
            this.doDisconnect( port );
            if(!(node is null )) node.notifyPortDisconnected(this, toDisconnect);
            return true;
        }
      }
      return false;
    }

  // ----------------------------------------------------------- virtual

  bool disconnectAll();

  bool isCompatible(PortInterface port);
  
  bool isComposite();
  
  bool isConnectedTo(PortInterface  port);
  
  @property PortInterface[] connections();

  /++
   + Should return a null reference if no data provided
   +/ 
  @property DataInterface data();

  @property DataTypeInfo dataType();
  
  @property NodeInterface node();
  
  // --------------------------------------------------------- protected
  protected void doConnect(PortInterface toConnect);
  protected void doDisconnect(PortInterface toDisconnect);
  
}


interface DataInterface{
  final bool isComposite(){
    if( subData is null ){ 
        return false;
    }else{
        return subData.length != 0;
    }
  }
  bool isSerializable();
  bool serialize( int stream );
  bool deSerialize( int stream );
  @property DataInterface[] subData();
  
}


//######################################################################
interface NodeInterface{
  @property NodeListenerInterface listener();
  @property void listener(NodeListenerInterface listnr);
  
  protected:
  final void notifyPortConnected(PortInterface myPort, PortInterface otherPort){
    if(listener !is null) listener.portConnected(myPort, otherPort);
  }
  final void notifyPortDisconnected(PortInterface myPort, PortInterface otherPort){
    if(listener !is null) listener.portDisconnected(myPort, otherPort);
  }
  final void notifyPortAdded(PortInterface addedPort){
    if(listener !is null) listener.portAdded(addedPort);
  }
  final void notifyPortRemoved(PortInterface removedPort){
    if(listener !is null) listener.portRemoved(removedPort);
  }
}


//######################################################################
interface NodeListenerInterface{
  void portConnected(PortInterface myPort, PortInterface otherPort);
  void portDisconnected(PortInterface myPort, PortInterface otherPort);
  void portAdded(PortInterface addedPort);
  void portRemoved(PortInterface removedPort);
}
