module test.core;

import kiwi.core.commons;
import kiwi.core.dynamic;
import std.stdio;

int main(){
  mixin(scopedBlock!"test:kiwi.core");

  log.foo();
  Port p1 = new kiwi.core.dynamic.Port();
  Port p2 = new kiwi.core.dynamic.Port();
  assert( !(p1 is null) && !(p2 is null));
  log.bar();
  p1.connect(p2);
  
 
  return true;
}
