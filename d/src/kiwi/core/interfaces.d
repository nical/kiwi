module kiwi.core.interfaces;

import kiwi.core.commons;
import kiwi.core.data;

alias string PortType;

interface Port{

  // --------------------------------------------------------------- implemented
  final bool connect(kiwi.core.interfaces.Port toConnect)
    in{ assert(!(toConnect is null),"Forbidden null parameter."); }
    body{    
    mixin(logFunction!"Port.connect");
    if( isCompatible(toConnect) && toConnect.isCompatible(this) ){
      this.doConnect(toConnect);
      toConnect.doConnect(this);
    }
    // TODO: notify listeners
    return false;
  }
  
  final bool disconnect(kiwi.core.interfaces.Port toDisconnect){
    mixin(logFunction!"Port.disconnect");
    // TODO
    return false;
  }

  // ------------------------------------------------------------------- virtual

  bool disconnectAll();

  bool isCompatible(kiwi.core.interfaces.Port port);
  
  @property Port[] connections();

  /++
   + Should return a null reference if no data provided
   +/ 
  @property Data data();

  @property PortType type();
  
  // ----------------------------------------------------------------- protected
  protected void doConnect(kiwi.core.interfaces.Port toConnect);
  protected void doDisconnect(kiwi.core.interfaces.Port toDisconnect);
  
}


interface Data{
  bool isComposite();
  bool isSerializable();
  bool serialize( int stream );
  bool deSerialize( int stream );
  @property const Data[] subContainers();
  
}


//##############################################################################
interface Node{
  @property NodeListener listener();
  @property void listener(NodeListener listnr);
}


//##############################################################################
interface NodeListener{
  
}
