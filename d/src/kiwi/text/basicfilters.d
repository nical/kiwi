module kiwi.text.basicfilters;


import kiwi.core.all;
import kiwi.core.algorithmwrapper;

import std.string;
import std.array;




// -------------------------------------------------- filter functions

void upperCaseFunction(string inputstr, ref string outputstr)
{
    outputstr = toUpper(inputstr);
}

void lowerCaseFunction(string inputstr, ref string outputstr)
{
    outputstr = toLower(inputstr);
}

void textReplaceFunction(string inputstr, string patternFrom, string patternTo, ref string outputstr)
{
    outputstr = std.array.replace(inputstr, patternFrom, patternTo );
}

// ------------------------------------------------------- creators



Node NewUpperCaseFilter()
{
    mixin( logFunction!"NewUpperCaseFilter" );
    return new Node
    (
        null, //node type info
        [ DeclareInput("Input text", Container!string.Type, READ ) ],
        [ DeclareOutput("Output text", new UserAllocatedDataStrategy(new Container!string, READ_WRITE)) ],
        WrapFunction( &upperCaseFunction )
    );
}

Node NewLowerCaseFilter()
{
    mixin( logFunction!"NewLowerCaseFilter" );
    return new Node
    (
        null, //node type info
        [ DeclareInput("Input text", Container!string.Type, READ ) ],
        [ DeclareOutput("Output text", new UserAllocatedDataStrategy(new Container!string, READ_WRITE)) ],
        WrapFunction( &lowerCaseFunction )
    );
}

Node NewTextReplaceFilter()
{
    return new Node
    (
        null, //node type info
        [
            DeclareInput("Input text", Container!string.Type, READ ),
            DeclareInput("Replace", Container!string.Type, READ ),
            DeclareInput("With", Container!string.Type, READ )
        ],
        [ DeclareOutput("Output text", new UserAllocatedDataStrategy(new Container!string, READ_WRITE)) ],
        WrapFunction( &textReplaceFunction )
    );
}





//              #######   #####    ####   #####    ####
//                 #      #       #         #     #    
//                 #      ###      ###      #      ### 
//                 #      #           #     #         #
//                 #      #####   ####      #     #### 



unittest{

    mixin(logTest!" kiwi.text.basicfilters");

    // take "<1> <2>!" as input, replace "<1>" by "Hello" and "<2>" by "Word", 
    // then turn it to upper case. 
    //                _________
    // "<1> <2>!" ---o         |
    //      "<1>" ---o replace |     _________
    //    "Hello" ---o_________o----o         |     ___________
    //                     "<2>" ---o replace |    |           |
    //                 "<World>" ---o_________o----o upperCase |
    //                                             |___________o---> output    
    //                                              

    auto upperCaseFilter = NewUpperCaseFilter(); 
    auto replaceFilter1  = NewTextReplaceFilter(); 
    auto replaceFilter2  = NewTextReplaceFilter(); 
    auto inputPhrase     = NewContainerNode( new Container!string("<1> <2>!") );
    auto inputTextP1     = NewContainerNode( new Container!string("<1>") );
    auto inputTextP2     = NewContainerNode( new Container!string("<2>") );
    auto inputTextHello  = NewContainerNode( new Container!string("Hello") );
    auto inputTextWorld  = NewContainerNode( new Container!string("World") );
    
    // Check references
    assert( inputPhrase.output() !is null );
    assert( inputPhrase.output().data !is null );

    assert( upperCaseFilter.input()  !is null );
    assert( upperCaseFilter.output() !is null );
    
    assert( inputPhrase.output().dataType !is null );
    assert( replaceFilter1.output().dataType !is null );

    // connect the nodes
    assert(    inputPhrase.output() >> replaceFilter1.input(0)  );
    assert(    inputTextP1.output() >> replaceFilter1.input(1)  );
    assert( inputTextHello.output() >> replaceFilter1.input(2)  );
    assert( replaceFilter1.output() >> replaceFilter2.input(0)  );
    assert(    inputTextP2.output() >> replaceFilter2.input(1)  );
    assert( inputTextWorld.output() >> replaceFilter2.input(2)  );
    assert( replaceFilter2.output() >> upperCaseFilter.input()  );

    // check some of the connections
    assert( inputPhrase.output().isConnected() );
    assert( replaceFilter1.input(0).isConnected() );
    assert( replaceFilter1.input(1).isConnected() );
    assert( replaceFilter1.input(2).isConnected() );    
    assert( inputPhrase.output().isConnectedTo( replaceFilter1.input(0) ) );
    
    // Update every filter in the right order
    // In the general case, use a NodeGroup, but this is not the object of this test suite
    replaceFilter1.update();
    replaceFilter2.update();
    upperCaseFilter.update();

    // print the intermediate results
    log.writeln( "input: ",     inputPhrase.output().dataAs!string );
    log.writeln( "Output(0): ", replaceFilter1.output().dataAs!string );
    log.writeln( "Output(1): ", replaceFilter2.output().dataAs!string );
    
    auto outputText = upperCaseFilter.output().dataAs!string;
    log.writeln( "Output(final): ", outputText );

    // Check the result
    assert(outputText == "HELLO WORLD!");
    
}
