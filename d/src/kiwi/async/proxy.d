module kiwi.async.proxy;

import kiwi.core.context;
import kiwi.core.commons;
import kiwi.async.transaction;

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

    void run( void delegate(bool) callback)
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
    
    void connect( OutputPortProxy output, void delegate(bool) callback = null )
    {
        proxyAsyncConnect(output, this, callback);
    }
    
    void disconnect( OutputPortProxy output, void delegate(bool) callback = null )
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
    
    void connect( ref const(InputPortProxy) input, void delegate(bool) callback = null )
    {
        proxyAsyncConnect( this, input, callback );
    }
    
    void disconnect( ref const(InputPortProxy) input, void delegate(bool) callback = null )
    {
        proxyAsyncDisconnect( this, input, callback );
    }
    
private:
    OutputPortID _id;
    ContextProxy _contextProxy;
}

alias uint TransactionID;

struct Transaction
{
    enum Type{ CONNECT, DISCONNECT, RUN };
    
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
    TransactionID   id;
}

private void proxyAsyncConnect( 
    ref const(OutputPortProxy) output
    , ref const(InputPortProxy) input
    , void delegate(bool) callback )
{
    uint transactionID = genTransactionID();
    
    Transaction transaction = {
        type: Transaction.Type.CONNECT,
        inputPort: input.id,
        outputPort: output.id,
        id: transactionID,
        //callerThreadId: thisTid
    };
    std.concurrency.send( input.context.tid, transaction, thisTid() );
    
    addTransactionCallback(transactionID, callback);
}

private void proxyAsyncDisconnect( 
    ref const(OutputPortProxy) output
    , ref const(InputPortProxy) input
    , void delegate(bool) callback )
{
    uint transactionID = genTransactionID();
    
    Transaction transaction = {
        type: Transaction.Type.DISCONNECT,
        inputPort: input.id,
        outputPort: output.id,
        id: transactionID,
        //callerThreadId: thisTid
    };
    std.concurrency.send( input.context.tid, transaction, thisTid() );
    
    addTransactionCallback(transactionID, callback);
}

private void proxyAsyncRun( ref PipelineProxy p, void delegate(bool) callback )
{
    uint transactionID = genTransactionID();
    
    Transaction transaction = {
        type: Transaction.Type.RUN,
        id: transactionID,
        //callerThreadId: thisTid
    };
    transaction.inputPort.node.pipeline = p.id;
    std.concurrency.send( p.context.tid, transaction, thisTid() );
    
    addTransactionCallback(transactionID, callback);
}
