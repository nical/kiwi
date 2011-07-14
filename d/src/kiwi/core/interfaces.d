module kiwi.core.interfaces;

import kiwi.core.data;

alias string PortType;

interface Port{

  // --------------------------------------------------------------- implemented
  final bool connect(kiwi.core.interfaces.Port toConnect){
    if( isCompatible(toConnect) && toConnect.isCompatible(this)){
      this.doConnect(toConnect);
      toConnect.doConnect(this);
    }
    
    // TODO: notify listeners
    return false;
  }
  
  final bool disconnect(kiwi.core.interfaces.Port toDisconnect){
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
