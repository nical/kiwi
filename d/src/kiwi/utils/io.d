module kiwi.utils.io;

import std.stdio;
import std.string;

enum{ reset = "\033[0m"
   , bold = "\033[1m"
   , italic = "\033[3m"
   , underlined = "\033[4m"
   , blue = "\033[34m"
   , lightBlue = "\033[1;34m"
   , green = "\033[1;32m"
   , lightGreen = "\033[1;32m"
   , red = "\033[31m"
   , lightRed = "\033[1;31m"
   , grey = "\033[1;30m"
   , purple = "\033[1;35m" };

enum{INFO_0   = 1
  , INFO_1    = 1 << 1
  , INFO_2    = 1 << 2
  , INFO_3    = 1 << 3
  , INFO_4    = 1 << 4
  , DEBUG_0   = 1 << 5
  , DEBUG_1   = 1 << 6
  , DEBUG_2   = 1 << 7
  , DEBUG_3   = 1 << 8
  , DEBUG_4   = 1 << 9
  , WARNING_0 = 1 << 10
  , WARNING_1 = 1 << 11
  , WARNING_2 = 1 << 12
  , WARNING_3 = 1 << 13
  , WARNING_4 = 1 << 14
  , USER_0    = 1 << 15
  , USER_1    = 1 << 16
  , USER_2    = 1 << 17
  , USER_3    = 1 << 18
  , USER_4    = 1 << 19
  , ERROR     = 1 << 20
  , TARGET_ALL= -1  
  , INFO_ALL  = 0x37  
  , DEBUG_ALL  = 0x37 << 5  
  , WARNING_ALL  = 0x37 << 10  
  , USER_ALL  = 0x37 << 15  
};

class OutputStream{
public:
  this(string[] args){ }
  this(){ }

  void print(T...)(T text){
    foreach(subText; text){
    static if( is(typeof(subText)==string) ){
      auto parts = subText.split("\n");
      bool first = true;
      foreach(part;parts){
        if((endl_ || !first)&&(!part.length==0)) {
          if(!first)stdout.writeln();
          indent();
        }
        stdout.write(part);
        endl_ = (part.length == 0);
        first = false;
      }
    }else{
      if(endl_) indent();
        stdout.write( subText );
      }
    }    
//stdout.write( text );
    
  }
  void println(T...)(T text){
    if(endl_) indent();
    stdout.writeln( text );
    endl_ = true;
  }
  void endl(int nLines = 1){
    for(;nLines > 0; --nLines){
      if(endl_ && usePrefix)
        stdout.write(targetPrefix_[EMPTY_]);
      stdout.writeln();
    }
    endl_ = true;
  }
  void printDebug(T...)(int level, T Text){
    if(!(targets_ & (DEBUG_0 << level))) return;
    if(endl_) indent(DEBUG_);
    stdout.writeln( Text );
    endl_ = true;
  }
  void printInfo(T...)(int level, T Text){
    if(!(targets_ & (INFO_0 << level))) return;
    if(endl_) indent(INFO_);
    stdout.writeln( Text );
    endl_ = true;
  }
  void printWarning(T...)(int level, T Text){
    if(!(targets_ & (WARNING_0 << level))) return;
    if(endl_) indent(WARNING_);
    stdout.writeln( red, Text, reset );
    endl_ = true;
  }
  void printUser(T...)(int level, T Text){
    if(!(targets_ & (USER_0 << level))) return;
    if(endl_) indent(USER_);
    stdout.writeln( Text );
    endl_ = true;
  }
  void printError(T...)( T Text ){
    if(!(targets_ & ERROR_)) return;
    if(endl_) indent(ERROR_);
    stdout.writeln(lightRed, Text, reset );
    endl_ = true;
  }
  
  void foo(){
    println(lightBlue,"foo",reset);
  }
  void bar(){
    println(lightBlue,"bar",reset);
  }
  void plop(){
    println(lightBlue,"plop",reset);
  }
  
  int indentation = 0;
  bool usePrefix = true;
  
private:
  enum{ INFO_, DEBUG_, WARNING_, USER_, ERROR_, EMPTY_ };
  
  void indent(int target = INFO_){
    if(usePrefix){
      stdout.write(targetPrefix_[target]);
    }
    for(int i = 0; i < indentation; ++i){
      stdout.write("    ");
    }
  }
  
  static immutable string[] targetPrefix_
    = ["[NFO]  ","[DBG]  ","[WNG]  "
      ,"[USR]  ","[ERR]  ","[   ]  "];
  // private properties
  bool endl_ = true;
  bool displayBlockText_ = true;
  bool useColors_ = true;
  int targets_ = TARGET_ALL;
}
