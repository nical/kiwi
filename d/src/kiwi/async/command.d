module kiwi.async.command;

import kiwi.async.proxy;
import kiwi.core.commons;
import kiwi.core.pipeline;
import kiwi.core.context;

import std.concurrency;


alias uint CommandID;

struct Command
{
    enum Type{ CONNECT, DISCONNECT, RUN, STOP };
    
    alias inputNode node;
    
    @property
    {
        NodeID inputNode() const pure
        {
            return inputPort.node;
        }
        
        NodeID outputNode() const pure
        {
            return outputPort.node;
        }
        
        PipelineID pipeline() const pure
        {
            return inputPort.node.pipeline;
        }
    }
    
    Type    type;
    InputPortID  inputPort;
    OutputPortID outputPort;
    //Tid     callerThreadId; // error: *p is not mutable
    int     contextIndex;
    CommandID   id;
}

struct CommandOutcome
{
    CommandID id;
    ContextProxy context;
    bool status;
}


void sendStopCommand(ref ContextProxy ctx, CommandCallback callback = null)
{
    uint commandID = genCommandID();
    
    Command command = {
        type: Command.Type.STOP,
        id: commandID,
        //callerThreadId: thisTid
    };
    std.concurrency.send( ctx.tid, command, thisTid() );
    
      addCommandCallback(commandID, callback);
}

alias void delegate(CommandOutcome) CommandCallback;


private CommandCallback[CommandID] _commandCallbacks;
private uint _nextCommandID;

uint genCommandID()
{
    return _nextCommandID++;
}

void addCommandCallback(CommandID id, CommandCallback callback)
{
    _commandCallbacks[id] = callback;
}

bool receiveCommands(ref Context ctx, PipelineState state)
{
    bool stop = false;
    std.concurrency.receive(
        (kiwi.async.command.Command cmd, Tid sender){
            log.writeln("received a command!");
            stop =  cmd.type == Command.Type.STOP;
            //std.concurrency.send( sender, CommandOutcome(cmd.id, ContextProxy(thisTid), true) );
            std.concurrency.send( sender, true, true);
        }
    );
    
    return !stop;
}

version(unittest)
{
    
    void workerThread()
    {
        import kiwi.core.nodefactory;
        Context ctx = Context(null, new NodeFactory);
        
        bool loop = true;
        while(loop)
        {
            loop = receiveCommands(ctx, null);
        }
    }
}

unittest
{
    import std.variant;
    import kiwi.utils.testing;
    auto unit = TestSuite("kiwi.async.command");
    
    auto workerTid = std.concurrency.spawn( &workerThread );

    ContextProxy ctx = ContextProxy(workerTid);

    sendStopCommand(ctx,null);
    
    std.concurrency.receive( 
        (Variant v){log.writeln("main thread received outcome");}
    );
    

}
