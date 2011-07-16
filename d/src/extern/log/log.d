module log;

import std.stdio;
import std.string;

enum{ RESET       = "\033[0m"
    , BOLD        = "\033[1m"
    , ITALIC      = "\033[3m"
    , UNDERLINED  = "\033[4m"
    , BLUE        = "\033[34m"
    , LIGHTBLUE   = "\033[1;34m"
    , GREEN       = "\033[1;32m"
    , LIGHTGREEN  = "\033[1;32m"
    , RED         = "\033[31m"
    , LIGHTRED    = "\033[1;31m"
    , GREY        = "\033[1;30m"
    , PURPLE      = "\033[1;35m"
};

enum{ INFO_0      = 1
    , INFO_1      = 1 << 1
    , INFO_2      = 1 << 2
    , INFO_3      = 1 << 3
    , INFO_4      = 1 << 4
    , DEBUG_0     = 1 << 5
    , DEBUG_1     = 1 << 6
    , DEBUG_2     = 1 << 7
    , DEBUG_3     = 1 << 8
    , DEBUG_4     = 1 << 9
    , WARNING_0   = 1 << 10
    , WARNING_1   = 1 << 11
    , WARNING_2   = 1 << 12
    , WARNING_3   = 1 << 13
    , WARNING_4   = 1 << 14
    , USER_0      = 1 << 15
    , USER_1      = 1 << 16
    , USER_2      = 1 << 17
    , USER_3      = 1 << 18
    , USER_4      = 1 << 19
    , ERROR       = 1 << 20
    , LOG_ALL     = -1  
    , INFO_ALL    = 0x37  
    , DEBUG_ALL   = 0x37 << 5  
    , WARNING_ALL = 0x37 << 10  
    , USER_ALL    = 0x37 << 15  
};




class LogStream{
public:
  this(string[] args){ }

  /++
   + Constructor
   +
   + Uses stdout as default output device.
   +/ 
  this(){
    _output = &stdout;
  }
  this(File* logDevice){
    _output = logDevice;
  }

  void write(T...)(T text){
    foreach(subText; text){
    static if( is(typeof(subText)==string) ){
      auto parts = subText.split("\n");
      //stdout.write("-|",parts.count,"|-");
      bool first = true;
      foreach(part;parts){
        //if((_endl || !first)&&(!part.length==0)) {
        if((_endl || !first)) {
          if(!first)_output.writeln();
          indent();
        }
        if(part.length==0 && part is parts[$-1]){
          _output.writeln();
        }    
        stdout.write(part);
        _endl = (part.length == 0);
        first = false;
      }
    }else{
      if(_endl) indent();
        _output.write( subText );
      }
    }    
//stdout.write( text );
  }
  
  void writeln(T...)(T text){
    if(_endl) indent();
    _output.writeln( text );
    _endl = true;
  }

  void endl(int nLines = 1){
    for(;nLines > 0; --nLines){
      if(_endl && usePrefix)
        _output.write(_targetPrefix[EMPTY_]);
      _output.writeln();
    }
    _endl = true;
  }

  void writeDebug(T...)(int level, T Text){
    if(!(_targets & (DEBUG_0 << level))) return;
    if(_endl) indent(DEBUG_);
    _output.writeln( Text );
    _endl = true;
  }

  void writeInfo(T...)(int level, T Text){
    if(!(_targets & (INFO_0 << level))) return;
    if(_endl) indent(INFO_);
    _output.writeln( Text );
    _endl = true;
  }

  void writeWarning(T...)(int level, T Text){
    if(!(_targets & (WARNING_0 << level))) return;
    if(_endl) indent(WARNING_);
    _output.writeln( RED, Text, RESET );
    _endl = true;
  }

  void writeUser(T...)(int level, T Text){
    if(!(_targets & (USER_0 << level))) return;
    if(_endl) indent(USER_);
    _output.writeln( Text );
    _endl = true;
  }

  void writeError(T...)( T Text ){
    if(!(_targets & ERROR_)) return;
    if(_endl) indent(ERROR_);
    _output.writeln(LIGHTRED, Text, RESET );
    _endl = true;
  }
  
  void foo(){
    writeln(LIGHTBLUE,"foo",RESET);
  }

  void bar(){
    writeln(LIGHTBLUE,"bar",RESET);
  }

  void plop(){
    writeln(LIGHTBLUE,"plop",RESET);
  }
  
  int indentation = 0;
  bool usePrefix = true;
  
private:
  enum{ INFO_, DEBUG_, WARNING_, USER_, ERROR_, EMPTY_ };
  
  void indent(int target = INFO_){
    if(usePrefix){
      _output.write(_targetPrefix[target]);
    }
    for(int i = 0; i < indentation; ++i){
      _output.write("    ");
    }
  }
  
  static immutable string[] _targetPrefix
    = ["[NFO]  ","[DBG]  ","[WRN]  "
      ,"[USR]  ","[ERR]  ","[   ]  "];

  // private properties
  bool _endl              = true;
  bool _displayBlockText  = true;
  bool _useColors         = true;
  int  _targets           = LOG_ALL;
  File* _output;
}


struct ScopedIndent{
  
  this(LogStream ls){
    logStream = ls;
    logStream.indentation++;
  }
  
  ~this(){
    logStream.indentation--;
  }
  LogStream logStream;
}

enum{ scopedIndent = "log.indentation++;scope(exit)log.indentation--;" };
string scopedBlock(string name)(){
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin block} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End block} \",RESET,\""~name~"\" );}}";
}

//              #######   #####    ####   #####    ####
//                 #      #       #         #     #   
//                 #      ###      ###      #      ### 
//                 #      #           #     #         #
//                 #      #####   ####      #     #### 

unittest{
  LogStream log = new LogStream();
  mixin(scopedBlock!"test:LogStream");
  log.write("line\n");
  log.writeWarning(1,"this is a warning\n");
  log.write("line\nline\nline\nline\n");
  log.writeln("line");
  log.write("\n\n\n\n");
  {
  mixin(scopedIndent);
  log.writeln("indent_1");
  {
  mixin(scopedIndent);
  log.writeln("indent_2");
  }
  log.writeln("indent_1");
  }
  log.writeln("indent_0");
}
