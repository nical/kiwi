module kiwi.core.commons;
/*
 * TODO: Dirty stuff here. needs cleanup
 * 
 * 
 */ 
public import dtools.logstream; 


LogStream log;

static this(){
  log = new LogStream();
}

enum{ scopedIndent = "log.indentation++;scope(exit)log.indentation--;" };

/*
// TODO: should be done with template mixin instead of text mixin
string scopedBlock(string name)(){
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin block} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End block} \",RESET,\""~name~"\" );}}";
}
*/
/*
mixin template scopedBlck(alias name){
    log.writeln( LIGHTBLUE, "{Begin block} ", RESET, name );
    log.indentation++;
    scope(exit){
        log.indentation--;
        log.writeln( LIGHTBLUE, "{End block} ", RESET, name );
    }
}
*/

// TODO: should be done with template mixin instead of text mixin
string logBlock(string name)(){
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin block} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End block} \",RESET,\""~name~"\" );}}";
}

// TODO: should be done with template mixin instead of text mixin
string logFunction(string name)(){
  return "debug{"
       ~ "log.writeln( LIGHTBLUE, \"{Begin function} \",RESET,\""~name~"\" );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTBLUE, \"{End function} \",RESET,\""~name~"\" );}}";
}

// TODO: should be done with template mixin instead of text mixin
string logTest(string name)(){
  return "debug{"
       ~ "log.writeln( LIGHTGREEN, \"{Begin test} \",RESET,BOLD,\""~name~"\",RESET );"
       ~ "log.indentation++;"
       ~ "scope(exit){ log.indentation--;"
       ~ "log.writeln( LIGHTGREEN, \"{End test} \",RESET,BOLD,\""~name~"\",RESET );}}";
}
