module kiwi.core.commons;

public import dtools.logstream; 


LogStream log;

static this(){
  log = new LogStream();
}

enum{ scopedIndent = "log.indentation++;scope(exit)log.indentation--;" };
string scopedBlock(string name)(){
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin block} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End block} \",RESET,\""~name~"\" );}}";
}

string logBlock(string name)(){
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin block} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End block} \",RESET,\""~name~"\" );}}";
}


string logFunction(string name)(){
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin function} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End function} \",RESET,\""~name~"\" );}}";
}
