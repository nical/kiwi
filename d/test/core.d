module test.core;

//import dtools.testing;

import kiwi.core.commons;
import kiwi.core.dynamic;
import kiwi.core.interfaces;
import kiwi.core.data;
import std.stdio;

enum{ NEVER_COMPATIBLE, ALWAYS_COMPATIBLE, SAME_DATATYPEINFO };

PortCompatibilityPolicy compatibilityCheck(int hint){
  switch(hint){
    case NEVER_COMPATIBLE : {
      return delegate(PortInterface thisPort, PortInterface otherPort){ return false; };
    }
    case ALWAYS_COMPATIBLE : {
      return delegate(PortInterface thisPort, PortInterface otherPort){ return true; };
    }
    case SAME_DATATYPEINFO : {
      return delegate(PortInterface thisPort, PortInterface otherPort){
        mixin( logFunction!"basicCompatibilityTest" );
        if( thisPort.dataTypeInfo() is null || otherPort.dataTypeInfo() is null ){
            return true;
        }else{
            return thisPort.dataTypeInfo() is otherPort.dataTypeInfo();  
        }
      };
    }
  }//switch
  return null;
}

T delegate(A) Fn2Dg(T, A...)(T function(A) f)
{
  struct tmp { T ret(A args){ return (cast(T function(A))this)(args); } };
  return &(cast(tmp*)f).ret;
}

bool basicCompatibilityTest(PortInterface thisPort, PortInterface otherPort){
  mixin( logFunction!"basicCompatibilityTest" );
  if( thisPort.dataTypeInfo() is null || otherPort.dataTypeInfo() is null ){
      return true;
  }else{
      return thisPort.dataTypeInfo() is otherPort.dataTypeInfo();  
  }
} 


class ContainerTest : DataInterface{
  static this(){
    _typeInfo = new DataTypeInfo("ContainerTest", null, false);
  }
  
  override bool isSerializable(){
    return false;
  }
  override bool serialize( DataStream stream ){ return false; }
  override bool deSerialize( const DataStream stream ){ return false; }
  override DataTypeInfo typeInfo(){ return _typeInfo; }
  static DataTypeInfo TypeInfo(){ return _typeInfo; }
  override @property DataInterface[] subData(){ return null; }
  
  private static DataTypeInfo _typeInfo; 
}

// ---------------------------------------------------------------------

int main(){
    
  mixin(logTest!"kiwi.core");
  //beginTesting("kiwi.core");


  auto p1 = new kiwi.core.dynamic.Port( null, ContainerTest.TypeInfo()
    , compatibilityCheck(SAME_DATATYPEINFO) );
  auto p2 = new kiwi.core.dynamic.Port( null, ContainerTest.TypeInfo() );

  assert( !(p1 is null) && !(p2 is null) );
  assert( p1.dataTypeInfo() is ContainerTest.TypeInfo() );
  assert( p2.dataTypeInfo() is ContainerTest.TypeInfo() );
  assert( !p1.isComposite() );
  assert( p1.connect(p2) );
  assert( p1.isConnectedTo(p2) );
  assert( p2.isConnectedTo(p1) );
  
  auto p3 = new kiwi.core.dynamic.Port( null, ContainerTest.TypeInfo()
    , compatibilityCheck(NEVER_COMPATIBLE) );
  auto p4 = new kiwi.core.dynamic.Port( null, ContainerTest.TypeInfo()
    , compatibilityCheck(ALWAYS_COMPATIBLE) );
  assert( !p3.connect(p4) );
  assert( !p3.isConnectedTo(p4) ); 
  
  assert( p2.connect(p4) );
  assert( p2.isConnectedTo(p4) ); 
  
  assert( p1.disconnect(p2) );
  assert( !p1.isConnectedTo(p2) );
  assert( !p2.isConnectedTo(p1) );
  
  //return endTesting();
  return 0;
}
