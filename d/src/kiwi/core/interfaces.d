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
        mixin(logFunction!"PortInterface.connect");
        if( isCompatible(toConnect) && toConnect.isCompatible(this) ){
            this.doConnect(toConnect);
            toConnect.doConnect(this);
            if(!(node is null )) node.notifyPortConnected(this, toConnect);
            return true;
        }
        log.writeWarning(4,"uncompatible ports");
        return false;
    }
  
    final bool disconnect(PortInterface toDisconnect)
    in
    {
        assert(!(toDisconnect is null),"Forbidden null parameter.");
    }
    body
    {
        mixin(logFunction!"PortInterface.disconnect");
  
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

    final bool isConnected(){
        return connections.length != 0;
    }

    final PortInterface connectedPort(int index = 0){
        return connections[index];
    }

    @property{
        PortInterface[] connections();

        /++
         + Should return a null reference if no data provided
         +/ 
        DataInterface data();
        
        DataTypeInfo dataTypeInfo();
  
        NodeInterface node();
    }

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
    bool serialize( DataStream stream );
    bool deSerialize( const DataStream stream );
    @property const(DataInterface[]) subData();
    abstract DataTypeInfo typeInfo();
  
}


//######################################################################
interface NodeInterface{

    @property{
        NodeListenerInterface listener();
        void listener(NodeListenerInterface listnr);    
    }//properties

    void update();

    /++
     + Input port accessor.
     +/ 
    PortInterface input(int index = 0);

    /++
     + Output port accessor.
     +/ 
    PortInterface output(int index = 0);

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


// -----------------------------------------------------------------------------


interface NodeListenerInterface{
    void portConnected(PortInterface myPort, PortInterface otherPort);
    void portDisconnected(PortInterface myPort, PortInterface otherPort);
    void portAdded(PortInterface addedPort);
    void portRemoved(PortInterface removedPort);
}
