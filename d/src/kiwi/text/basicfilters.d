module kiwi.text.basicfilters;

import kiwi.text.data;
import kiwi.core.commons;
import kiwi.core.interfaces;
import kiwi.core.dynamic;
import kiwi.core.base;

import std.string;


class UpperCaseFilter : kiwi.core.dynamic.NodeInterface{

    this(){
        mixin( logFunction!"UpperCaseFilter.constructor" );
        _input = new Port(this, cast(DataInterface)null);
        _output = new Port(this, new PlainTextContainer);
    }

    override void update(){
        mixin( logFunction!"UpperCaseFilter.update" );
                
        if( !_input.isConnected() ){
            log.writeError("UpperCaseFilter.update: input port not connected!\n");
            return;
        }
        
        PlainTextContainer inputData = cast(PlainTextContainer) _input.connectedPort().data();
        PlainTextContainer outputData = _output.dataAs!PlainTextContainer();
        
        if(inputData is null || outputData is null ){
            log.writeError("UpperCaseFilter.update: nil data\n");
            return;
        }
        
        outputData.textData = toupper(inputData.textData);
        log.write("input: ", inputData.textData, "\n");
        log.write("output: ", outputData.textData, "\n");
    }

    @property{
        override NodeListenerInterface listener(){return _listener;}
        override void listener(NodeListenerInterface val){_listener = val;}
    }
    
    override PortInterface input(int index = 0){ return _input; }
    override PortInterface output(int index = 0){ return _output; }
    Port input()  { return _input;  } //temp
    Port output() { return _output; } //temp
     
private:    
    Port _input; 
    Port _output;
    NodeListenerInterface _listener;
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
