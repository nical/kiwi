module kiwi.text.basicfilters;

import kiwi.text.data;
import kiwi.core.commons;
import kiwi.core.interfaces;
import kiwi.core.dynamic;
import kiwi.core.base;

import std.string;


class UpperCaseFilter : DynamicNode{

    this(){
        mixin( logFunction!"UpperCaseFilter.constructor" );
        inputs ~= new PermissiveInputPort(this);
        outputs ~= new PermissiveOutputPort(this);
    }

    override void update(){
        mixin( logFunction!"UpperCaseFilter.update" );
                
        if( !inputs[0].isConnected() ){
            log.writeError("UpperCaseFilter.update: input port not connected!\n");
            return;
        }
        
        PlainTextContainer inputData
            = cast(PlainTextContainer) inputs[0].connectedPort().data();
        PlainTextContainer outputData
            = outputs[0].dataAs!PlainTextContainer();
        
        if(inputData is null || outputData is null ){
            log.writeError("UpperCaseFilter.update: nil data\n");
            return;
        }
        
        outputData.textData = toupper(inputData.textData);
        log.write("input: ", inputData.textData, "\n");
        log.write("output: ", outputData.textData, "\n");
    }
}

unittest{

    mixin(logTest!"kiwi.text.basicfilters");
    //beginTesting("kiwi.core");

    auto inputNode = new ContainerNode( new PlainTextContainer("hello world!") );

    auto filter    = new UpperCaseFilter(); 

    assert( inputNode.output() !is null );
    assert( inputNode.output().data !is null );

    assert( filter.input()  !is null );
    assert( filter.output() !is null );
    assert( filter.output().data !is null );

    assert( inputNode.output().connect( filter.input() ) );
    assert( inputNode.output().isConnected() );
    assert( filter.input().isConnected() );
    assert( inputNode.output().isConnectedTo(filter.input() ) );
    
    filter.update();

    auto outputText = cast(PlainTextContainer) filter.output().data;
    assert(outputText !is null);
    
    log.writeln( "Output: ", outputText.textData );
}
