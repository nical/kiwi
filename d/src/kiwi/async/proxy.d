module kiwi.async.proxy;

import kiwi.core.context;
import kiwi.core.commons;
import kiwi.async.command;

import std.concurrency;

struct ContextProxy
{
    this( ref Context ctx )
    {
        context = &ctx;
        tid = std.concurrency.thisTid();
    }
    
    this( Tid thread, int idx = 0 )
    {
        index   = idx;
        tid     = thread;
    }


    @property
    {
        bool sameThread() const
        {
            return tid == thisTid();
        }
    }
    
    union
    {
        Context*   context;
        int        index;
    }
    Tid tid;
}

struct PipelineProxy
{

    void run( void delegate(CommandOutcome) callback)
    {
        proxyAsyncRun(this, callback);
    }
    PipelineID id;
    ContextProxy context;
}

struct NodeProxy
{
    this(NodeID nodeid, ContextProxy contextproxy)
    {
        _id = nodeid;
        _contextProxy = contextproxy;
    }
    
    @property
    {
        NodeID id() const pure
        {
            return _id;
        }
        
        void id(NodeID val)
        {
            _id = val;
        }
        
        ContextProxy context()
        {
            return _contextProxy;
        }
    }
    
    InputPortID inputID(int index)
    {
        return InputPortID(_id, cast(ubyte)index);
    }
    
    InputPortProxy input(int index)
    {
        return InputPortProxy(InputPortID(_id, cast(ubyte)index), _contextProxy);
    }
    
    OutputPortProxy output(int index)
    {
        return OutputPortProxy(OutputPortID(_id, cast(ubyte)index), _contextProxy);
    }
    
private:
    NodeID _id;
    ContextProxy _contextProxy;
}

struct InputPortProxy
{
    this(InputPortID pid, ContextProxy contextproxy)
    {
        _id = pid;
        _contextProxy = contextproxy;
    }
    
    @property
    {
        InputPortID id() const pure
        {
            return _id;
        }
        
        void id(InputPortID val) pure
        {
            _id = val;
        }
        
        ContextProxy context() const pure
        {
            return (cast(InputPortProxy)this)._contextProxy;
        }
    }
    
    void connect( OutputPortProxy output, void delegate(CommandOutcome) callback = null )
    {
        proxyAsyncConnect(output, this, callback);
    }
    
    void disconnect( OutputPortProxy output, void delegate(CommandOutcome) callback = null )
    {
        proxyAsyncDisconnect(output, this, callback);
    }
    
private:
    InputPortID _id;
    ContextProxy _contextProxy;
}


struct OutputPortProxy
{
    this(OutputPortID pid, ContextProxy contextproxy)
    {
        _id = pid;
        _contextProxy = contextproxy;
    }
    
    @property
    {
        OutputPortID id() const pure
        {
            return _id;
        }
        
        void id(OutputPortID val)
        {
            _id = val;
        }
    }
    
    void connect( ref const(InputPortProxy) input, void delegate(CommandOutcome) callback = null )
    {
        proxyAsyncConnect( this, input, callback );
    }
    
    void disconnect( ref const(InputPortProxy) input, void delegate(CommandOutcome) callback = null )
    {
        proxyAsyncDisconnect( this, input, callback );
    }
    
private:
    OutputPortID _id;
    ContextProxy _contextProxy;
}




private void proxyAsyncConnect( 
    ref const(OutputPortProxy) output
    , ref const(InputPortProxy) input
    , void delegate(CommandOutcome) callback )
{
    uint commandID = genCommandID();
    
    Command command = {
        type: Command.Type.CONNECT,
        inputPort: input.id,
        outputPort: output.id,
        id: commandID,
        //callerThreadId: thisTid
    };
    std.concurrency.send( input.context.tid, command, thisTid() );
    
    addCommandCallback(commandID, callback);
}

private void proxyAsyncDisconnect( 
    ref const(OutputPortProxy) output
    , ref const(InputPortProxy) input
    , void delegate(CommandOutcome) callback )
{
    uint commandID = genCommandID();
    
    Command command = {
        type: Command.Type.DISCONNECT,
        inputPort: input.id,
        outputPort: output.id,
        id: commandID,
        //callerThreadId: thisTid
    };
    std.concurrency.send( input.context.tid, command, thisTid() );
    
    addCommandCallback(commandID, callback);
}

private void proxyAsyncRun( ref PipelineProxy p, void delegate(CommandOutcome) callback )
{
    uint commandID = genCommandID();
    
    Command command = {
        type: Command.Type.RUN,
        id: commandID,
        //callerThreadId: thisTid
    };
    command.inputPort.node.pipeline = p.id;
    std.concurrency.send( p.context.tid, command, thisTid() );
    
    addCommandCallback(commandID, callback);
}
