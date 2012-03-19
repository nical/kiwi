module kiwi.core.pipeline;

import std.variant;
import std.container : SList;

//import kiwi.core.port;
import kiwi.core.context;
import kiwi.core.commons;
import kiwi.core.node;
import kiwi.utils.datastructures : PiecewiseVector;

struct Pipeline
{
    this( Context* ctx )
    {
        _context = ctx;
    }

    @property 
    {
        Context* context() { return _context; }
    }
    
    int instanciateNode( NodeTypeID type )
    {
        auto info = _context.nodeFactory.nodeTypeInfo(type);
        assert(info !is null);
        
        _nodes.length = _nodes.length + 1;
        _nodes[_nodes.length-1].initialize(&this, info);
        return _nodes.length-1;
    }
    
    ref inout(Node) node(int index) inout
    {
        return _nodes[index];
    }
    
    ref inout(Node) node(NodeID nid) inout
    {
        return _nodes[nid.index];
    }
    
    bool update(uint hints = 0)
    {
        return _updater.update(this,hints);
    }

    void touch(int nodeIndex) pure
    {
        _touchList ~= nodeIndex;
    }
    
    void touch(ref Node n) pure
    {
        _touchList ~= nodeIndex(n);
    }

    int nodeIndex(ref const(Node) n) const pure // TODO
    {
        assert(&(n.pipeline()) is &this);
        for(int i = 0; i < _nodes.length; ++i)
        {
            if(&_nodes[i] is &n)
                return i;
        }
        assert(false);
    }

private:
    Context* _context;
    PiecewiseVector!(Node,8) _nodes;
    int[]   _touchList;
    PipelineUpdater _updater;
}

interface PipelineUpdater
{
    bool update( ref Pipeline p, uint hints );
    //bool updateStep( ref Pipeline p, uint hints, PipelineState state);
    void reset( ref Pipeline p );
}

interface PipelineState
{
    @property
    {
        uint hash();
        bool finished();
    }
}

unittest
{
    import kiwi.utils.testing;
    auto unit = TestSuite("kiwi.core.pipeline");

    Context ctx;
    Pipeline p1 = Pipeline(&ctx);
    
    unit.test( p1.context is &ctx, "Checking pipeline's context (passed in constructor)." );

    Pipeline* pp2 = new Pipeline(&ctx);
    delete pp2;
    
}
