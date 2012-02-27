module kiwi.core.commons;

enum { READ = 1, WRITE = 2, SIGNAL = 4, OPT = 32 };

struct NodeTypeID
{
    uint index;
    static @property NodeTypeID Null()
    {
        return NodeTypeID(0);
    }
}


alias const(object.TypeInfo) DataTypeID; 


class NotImplementedYetException : Exception
{
    this(string msg, string file = null, uint line = 0)
    {
        super(msg ~ " is not implemented yet.", file, line);
    }
}

auto NotImplemented(string file = __FILE__, int line = __LINE__)(string name) pure
{
    return new NotImplementedYetException(name,file,line);
}


// instance of the log object
LogStream log;
static this()
{
    log = new LogStream();
}


public import kiwi.utils.log;
/+

enum{ scopedIndent = "log.indentation++;scope(exit)log.indentation--;" };


// TODO: should be done with template mixin instead of text mixin
string logBlock(string name)()
{
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin block} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End block} \",RESET,\""~name~"\" );}}";
}

// TODO: should be done with template mixin instead of text mixin
string logFunction(string name)()
{
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin function} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End function} \",RESET,\""~name~"\" );}}";
}

// TODO: should be done with template mixin instead of text mixin
string logTest(string name)()
{
  return "debug{"
       ~ "log.writeln( LIGHTGREEN, \"{Begin test} \",RESET,BOLD,\""~name~"\",RESET );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTGREEN, \"{End test}   \",RESET,BOLD,\""~name~"\",RESET );}}";
}
+/
