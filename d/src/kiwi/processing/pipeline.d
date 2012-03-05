module kiwi.processing.pipeline;

public import kiwi.core.pipeline;
public import kiwi.core.context;
public import kiwi.core.node;
public import kiwi.core.commons;

/+
class LazyPipelineUpdater : PipelineUpdater
{
    
}
+/

class RecursivePipelineUpdater : PipelineUpdater
{
    enum { READY = 1 };
    
    this(NodeID rootId)
    {
        _rootNode = rootId;
    }
    
    bool update( ref Pipeline p, uint hints )
    {
        Node* root = &p.node(_rootNode);
        
        if (!(_state & READY))
            genUpdateList( root );
        
        foreach ( n ; _updateList ) 
            if (!n.update())
                return false;
        return true;
    }
    
    void markDirty()
    {
        _state &= (~READY);
    }
    
    void genUpdateList( Node* n )
    {
        foreach (pn ; n.previousNodes)
        {
            bool found = true;
            foreach (markedNode ; _updateList)
            {
                if (pn is markedNode)
                    found = true;
            }
            if (!found)
            {
                _updateList ~= pn;
                genUpdateList(pn);
            }
        }
        _state &= READY;
    }
    
    //bool updateStep( ref Pipeline p, uint hints, PipelineState state);
    void reset( ref Pipeline p )
    {
        
    }
    
    @property
    {
        NodeID rootNode()
        {
            return _rootNode;
        }
        
        void rootNode(NodeID val)
        {
            _rootNode = val;
        } 
    }
    
private:
    NodeID  _rootNode;
    uint    _state;
    Node*[] _updateList;
}

unittest
{
    import kiwi.utils.testing;
    import kiwi.utils.hstring; 
    import kiwi.core.nodeinfo; 
    import kiwi.core.nodefactory; 
    auto unit = TestSuite("kiwi.processing.pipeline");
    
    alias CompileHash name;
    NodeTypeInfo ntinfo = {
        name : name!"NodeName",
        inputs : [
            { name!"in#1", typeid(int), READ },
            { name!"in#2", typeid(int), READ }
        ],
        outputs : [
            { name!"out#1", typeid(int), READ },
            { name!"out#2", typeid(int), READ }
        ]
    };
    
    Context ctx = Context( null, new NodeFactory);
    ctx.registerNodeType( ntinfo );
    
    Pipeline p = Pipeline(&ctx);
    
    //p.instanciateNode()
    
}
