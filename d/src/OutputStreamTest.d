#!/usr/bin/rdmd
import kiwi.utils.io;
import std.stdio;
import std.array;
import std.string;



void foo(T...)(T text){
  foreach(subText; text){
    static if( is(typeof(subText)==string) ){
      auto parts = subText.split("\n");
      foreach(part;parts){
        stdout.write("#");
        stdout.writeln(part);
      }
    }else{
      stdout.write( subText );
    }
  }
}



int main(string[] args){
  auto output = new kiwi.utils.io.OutputStream(args);
  
  output.print("hi! ");
  
  output.println("kiwi.utils.io test");
  output.indentation++;
    output.println("indentation lv1");
    output.foo();
    output.indentation++;
      output.println("indentation lv2");
      output.endl(3);
      output.bar();
      output.indentation--;
    output.println("indentation lv1");
    output.indentation--;
  output.println("indentation lv0");
  output.plop();
  output.endl();
  output.println(red,"text in ", underlined,"red", reset );
  output.printUser(0,"User target");
  output.printInfo(0,"Info target");
  output.printDebug(0,"Debug target");
  output.printWarning(0,"Warning target");
  output.printError("Error target");

  
  output.print("hi!\nwhat'sup?\nnoting...");
  output.print("no,really, nothing\n");

  auto tmp = "\nhello\n".split("\n");
  writeln(tmp.length);
  return 0;
}
