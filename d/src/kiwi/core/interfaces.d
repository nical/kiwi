module kiwi.core.interfaces;

import kiwi.core.commons;
import kiwi.core.data;

interface PortInterface{

  // --------------------------------------------------------------- implemented
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
        // TODO: notify listeners
        return false;
    }
  
  final bool disconnect(PortInterface toDisconnect)
    in
    {
      assert(!(toConnect is null),"Forbidden null parameter.");
    }
    body
    {
      mixin(logFunction!"Port.disconnect");
      
      if( !isConnected(toDisconnect) ) 
        return false;
      
      foreach( port ; _connections ){
        if( port is toDisconnect ){
            port.doDisconnect( this );
        }
      }
      
      // TODO
      return false;
    }

  // ------------------------------------------------------------------- virtual

  bool disconnectAll();

  bool isCompatible(PortInterface port);
  
  bool isComposite();
  
  @property PortInterface[] connections();

  /++
   + Should return a null reference if no data provided
   +/ 
  @property DataInterface data();

  @property DataTypeInfo type();
  
  // ----------------------------------------------------------------- protected
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


//##############################################################################
interface NodeInterface{
  @property NodeListenerInterface listener();
  @property void listener(NodeListenerInterface listnr);
}


//##############################################################################
interface NodeListenerInterface{
  void portConnected(PortInterface myPort, PortInterface otherPort);
  void portDisconnected(PortInterface myPort, PortInterface otherPort);
  void portAdded(PortInterface addedPort);
  void portRemoved(PortInterface removedPort);
}
