module test.core;

import std.stdio;
//import dtools.testing;

import kiwi.core.all;

// ---------------------------------------------------------------------

int main()
{
    log.write("\n\nKiwi!\n\n");  
    
    version(Win32)
    {
	    char buf;
		stdin.read(buf);
    }
    //return endTesting();
    return 0;
}
