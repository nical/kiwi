module kiwi.core.interfaces;

import kiwi.core.data;


alias string PortType;


// nb Ports
// isComposite
// model (ContainerInfo...)
// port Type
// compatible port types
// max connected ports
// onUpdate()
interface Port{


  // --------------------------------------------------------------- implemented
  final bool connect(kiwi.core.interfaces.Port toConnect){
    //if( this.connectableTypes.contains(toConnect.type) || toConnect.connectableTypes.contains(this.type) )
    if( isCompatible(toConnect) && toConnect.isCompatible(this)){
      this.doConnect(toConnect);
      toConnect.doConnect(this);
    }
    
    // notify listeners
    return false;
  }
  
  final bool disconnect(kiwi.core.interfaces.Port toDisconnect){
    return false;
  }

  // ------------------------------------------------------------------- virtual
  @property PortType type();


  bool disconnectAll();

  bool isCompatible(kiwi.core.interfaces.Port port);
  
  @property Port[] connections();


  // ----------------------------------------------------------------- protected
  protected void doConnect(kiwi.core.interfaces.Port toConnect);
  protected void doDisconnect(kiwi.core.interfaces.Port toDisconnect);
}





//##############################################################################
interface Node{

}


//##############################################################################
interface NodeListener{
  

}
