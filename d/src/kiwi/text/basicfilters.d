module kiwi.text.basicfilters;

import kiwi.text.data;
import kiwi.commons;
import kiwi.core;
import kiwi.data;
import kiwi.dynamic.node;
import kiwi.dynamic.port;
import kiwi.dynamic.compatibility;

import std.string;


void applyUpperCase(Data[] input, Data[] output )
{
    if(input is null     || output is null)     return;
    if(input.length == 0 || output.length == 0) return;
    
    auto inputData  = cast(PlainTextContainer) input[0];
    auto outputData = cast(PlainTextContainer) output[0];

    if(inputData is null || outputData is null)  return;
    
    outputData.text = toupper(inputData.text);
}

Node NewUpperCaseFilter()
{
    mixin( logFunction!"NewUpperCaseFilter" );
    InputPortInitializer[] inputs   = [];
    OutputPortInitializer[] outputs = [];
    inputs  ~= InputPortInitializer("Input text", new DataTypeCompatibility(PlainTextContainer.Type));
    outputs ~= OutputPortInitializer("Output text", PlainTextContainer.Type);
    return new DynamicNode( inputs, outputs, &applyUpperCase );
}

unittest{

    mixin(logTest!" kiwi.text.basicfilters");
    //beginTesting("kiwi.core");

    auto filter     = NewUpperCaseFilter(); 
    auto inputNode  = NewContainerNode( new PlainTextContainer("hello world!") );
    
    assert( inputNode.output() !is null );
    assert( inputNode.output().data !is null );

    assert( filter.input()  !is null );
    assert( filter.output() !is null );
    
    assert( inputNode.output().dataType !is null );
    log.writeln(inputNode.output().dataType.name);
    //log.writeln(filter.input().data.Type.name;);
    assert( inputNode.output().connect( filter.input() ) );
    assert( inputNode.output().isConnected() );
    assert( filter.input().isConnected() );
    assert( inputNode.output().isConnectedTo(filter.input() ) );
    
    filter.update();

    auto outputText = cast(PlainTextContainer) filter.output().data;
    assert(outputText !is null);
    
    log.writeln( "Output: ", outputText.text );
}
