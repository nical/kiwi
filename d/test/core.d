module test.core;

//import dtools.testing;

import kiwi.commons;
import kiwi.dynamic.port;
import kiwi.dynamic.node;
import kiwi.core;
import kiwi.data;
import std.stdio;

enum{ NEVER_COMPATIBLE, ALWAYS_COMPATIBLE, SAME_DATATYPEINFO };
/*
PortCompatibilityPolicy compatibilityCheck(int hint){
  switch(hint){
    case NEVER_COMPATIBLE : {
      return delegate(OutputPort thisPort, InputPort otherPort){ return false; };
    }
    case ALWAYS_COMPATIBLE : {
      return delegate(OutputPort thisPort, InputPort otherPort){ return true; };
    }
    case SAME_DATATYPEINFO : {
      return delegate(OutputPort thisPort, InputPort otherPort){
        mixin( logFunction!"basicCompatibilityTest" );
        if( thisPort.dataType() is null || otherPort.dataType() is null ){
            return true;
        }else{
            return thisPort.dataType() is otherPort.dataType();  
        }
      };
    }
  }//switch
  return null;
}
*/
T delegate(A) Fn2Dg(T, A...)(T function(A) f)
{
  struct tmp { T ret(A args){ return (cast(T function(A))this)(args); } };
  return &(cast(tmp*)f).ret;
}
/*
bool basicCompatibilityTest(OutputPort thisPort, InputPort otherPort){
  mixin( logFunction!"basicCompatibilityTest" );
  if( thisPort.dataType() is null || otherPort.dataType() is null ){
      return true;
  }else{
      return thisPort.dataType() is otherPort.dataType();  
  }
} 
*/

class ContainerTest : kiwi.core.Data{
  static this(){
    _typeInfo = new DataTypeInfo("ContainerTest", null, false);
  }
  
  override bool serialize( DataStream stream ){ return false; }
  override bool deSerialize( const DataStream stream ){ return false; }
  override DataTypeInfo type(){ return _typeInfo; }
  static DataTypeInfo Type(){ return _typeInfo; }
  override @property Data[] subData(){ return []; }
  
  private static DataTypeInfo _typeInfo; 
}

// ---------------------------------------------------------------------

int main(){
    
  mixin(logTest!"kiwi.core");
  //beginTesting("kiwi.core");

  log.plop();
  auto p1 = new kiwi.dynamic.port.DynamicOutputPort( null, ContainerTest.Type() );
  log.plop();
  auto p2 = new kiwi.dynamic.port.DynamicInputPort( null );

  auto p3 = new kiwi.dynamic.port.DynamicOutputPort( null, ContainerTest.Type() );
  auto p4 = new kiwi.dynamic.port.DynamicInputPort( null );
  
  assert( !(p1 is null) && !(p2 is null) );
  assert( !p1.isComposite() );
  assert( p1.connect(p2) );
  assert( p1.isConnectedTo(p2) );
  assert( p2.isConnectedTo(p1) );
  
  assert( p1.disconnect(p2) );
  assert( !p1.disconnect(p2) ); // should fail and return false without crash
  assert( !p2.disconnect(p1) ); // should fail and return false without crash

  assert( !p1.isConnectedTo(p2) );
  assert( !p2.isConnectedTo(p1) );
  
  assert( p2.connect(p1) );
  assert( p1.isConnectedTo(p2) );
  assert( p2.isConnectedTo(p1) );
  
  assert( p2.disconnect(p1) );
  assert( !p1.isConnectedTo(p2) );
  assert( !p2.isConnectedTo(p1) );
  
  //return endTesting();
  return 0;
}
