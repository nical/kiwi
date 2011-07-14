module kiwi.core.dynamic;

import kiwi.core.interfaces;
import kiwi.core.data;



interface CompatibilityPolicy{
  bool isCompatible(kiwi.core.interfaces.Port thisPort, kiwi.core.interfaces.Port port);
}



//##############################################################################
class Node : kiwi.core.interfaces.Node {

  override @property NodeListener listener(){
    return _listener;
  }
  override @property void listener(NodeListener listnr){
      _listener = listnr;
  }

private:
  NodeListener _listener;
}


//##############################################################################
class Port : kiwi.core.interfaces.Port{

  public override bool isCompatible(kiwi.core.interfaces.Port port){
    return _compatibility.isCompatible(this,port);
  }

  public override bool disconnectAll(){
    return false;
    // TODO
  }

  protected override void doConnect(kiwi.core.interfaces.Port toConnect){
    
  }

  protected override void doDisconnect(kiwi.core.interfaces.Port toConnect){

  }

  override @property Data data(){
    return _data;
  }
  override @property PortType type(){ return "TODO"; }
  override @property kiwi.core.interfaces.Port[] connections(){ return _connections; }

  protected CompatibilityPolicy _compatibility;
  protected kiwi.core.interfaces.Port[] _connections;
  protected kiwi.core.interfaces.Data _data;
}

unittest{
  auto p1 = new kiwi.core.dynamic.Port();
  auto p2 = new kiwi.core.dynamic.Port();

  p1.connect(p2);
  
}

