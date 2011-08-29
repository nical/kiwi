module dtools.logstream;

import std.stdio;
import std.string;

/**
 * Constants providing the character sequences to add colors in a terminal.
 */ 
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

/**
 * The log targets
 */ 
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



/**
 * Log class to ease debugging
 */ 
class LogStream
{
public:

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

    void write(T...)(T text)
    {
        if(_output == null) return;
        foreach( subText ; text )
            writeSingle(subText);
    }

    protected void writeSingle(T)(T text)
    {
        static if( is(typeof(text)==string) )
        {
            auto parts = text.split("\n");

            for( int i = 0; i < parts.length; ++i )
            {
                if (_endl && parts[i] != "") indent();
                if (parts[i] != "") _output.write( parts[i] );
                if ( i != parts.length-1 )
                {
                    //stdout.write(GREEN, "x",i,"/",parts.length, RESET);
                    _output.writeln();
                    _endl = true;
                }
                else
                {
                    _endl = false;
                    if (parts[i] == "" && i > 0)
                        _endl = true;
                }
            }
        }
        else
        {
            if(_endl) indent();
            _output.write( text );
        }    
    }

    void writeln(T...)(T text){
        write(text, "\n");
    }

    void endl(int nLines = 1){
        if( _output is null ) return;
        for(;nLines > 0; --nLines){
            if(_endl && usePrefix)
                _output.write(GREY, _targetPrefix[EMPTY_], RESET);    
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
        writeln(PURPLE,"foo",RESET);
    }

    void bar(){
        writeln(PURPLE,"bar",RESET);
    }

    void plop(){
        writeln(PURPLE,"plop",RESET);
    }
    
    int indentation = 0;
    bool usePrefix = true;
    
private:
  enum{ INFO_, DEBUG_, WARNING_, USER_, ERROR_, EMPTY_ };
  
  void indent(int target = INFO_){
    if( _output is null ) return;
    if(usePrefix){
      _output.write(GREY, _targetPrefix[target], RESET);
    }
    for(int i = 0; i < indentation; ++i){
      _output.write("    ");
    }
  }
  
  static immutable string[] _targetPrefix
    = ["[NFO]  ","[DBG]  ","[WRN]  "
      ,"[USR]  ","[ERR]  ","[   ]  "];

  // private propertiesw
  bool _endl              = true;
  bool _displayBlockText  = true;
  bool _useColors         = true;
  int  _targets           = LOG_ALL;
  int  _currentTarget     = 0;
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



//              #######   #####    ####   #####    ####
//                 #      #       #         #     #   
//                 #      ###      ###      #      ### 
//                 #      #           #     #         #
//                 #      #####   ####      #     #### 


unittest
{
    stdout.writeln(GREY, "[NFO]  ", GREEN, "{Begin test} logstream", RESET);
    
    LogStream logs = new LogStream();
    
    logs.indentation++;

    logs.write("line\n");
    logs.writeWarning(1,"this is a warning\n");
    logs.write("line\nline\nline\nline\n");
    logs.writeln("line");
    
    logs.write("a\n", "b", "\n", "c \n");
    logs.write("f",  "e",  "d\n");
    logs.endl();
    logs.write("1\n2","\n", "a-","-b\n");
    logs.write("then 2 blank lines\n");
    logs.write("\n\n");
    logs.write("then 2 blank lines again\n");
    logs.write(" \n"," \n");
    logs.write("on ", "the ");
    logs.write("same line\n");
    logs.write("");
    logs.write("");
    logs.write("numbers:", 42, " ", 3.14);
    logs.write( 1337, "\n");
    stdout.writeln(GREY, "[NFO]  ", GREEN, "{End test} logstream", RESET);
    
    // create a log stream that prints nowhere
    LogStream nullLogs = new LogStream(null);
    nullLogs.write("THIS SHOULD NOT BE PRINTED!");
    nullLogs.plop();
    nullLogs.foo();
    nullLogs.bar();
    nullLogs.endl();
}

