module test.core;

import kiwi.core.commons;
import kiwi.core.dynamic;
import kiwi.core.interfaces;
import kiwi.core.data;
import std.stdio;

class CompatibilityTest : CompatibilityPolicy{
    override bool isCompatible(PortInterface thisPort, PortInterface otherPort){
        mixin( logFunction!"CompatibilityTest" );
        if( thisPort.dataType() is null || otherPort.dataType() is null ){
            return true;
        }else{
            return thisPort.dataType() is otherPort.dataType();  
        }
    } 
}

class ContainerTest : DataInterface{
  static this(){
    _typeInfo = new DataTypeInfo("ContainerTest", null, false);
  }
  
  override bool isSerializable(){
    return false;
  }
  override bool serialize( int stream ){ return false; }
  override bool deSerialize( int stream ){ return false; }
  override @property DataInterface[] subData(){ return null; }
  static DataTypeInfo typeInfo(){ return _typeInfo; }
  private static DataTypeInfo _typeInfo; 
}

// ---------------------------------------------------------------------

int main(){
    
  mixin(logTest!"kiwi.core");

  Port p1 = new kiwi.core.dynamic.Port( ContainerTest.typeInfo(), new CompatibilityTest );
  Port p2 = new kiwi.core.dynamic.Port( ContainerTest.typeInfo() );
  assert( !(p1 is null) && !(p2 is null) );
  assert( p1.dataType() is ContainerTest.typeInfo() );
  assert( p2.dataType() is ContainerTest.typeInfo() );
  assert( !p1.isComposite() );
  assert( p1.connect(p2) );
  
  return true;
}
