#ifndef KIWI_CORE_PIPELINE_HPP
#define KIWI_CORE_PIPELINE_HPP

#include "kiwi/core/Commons.hpp"
#include <vector>

namespace kiwi{
namespace core{

class Data;
class Node;
class Pipeline;

/**
 * Interface for immutable logic bloc.
 *
 * This is the class to inherit from in order to create "compiled" pipelines.
 * Custom pipelines should inherit from Pipeline instead.
 */ 
class Procedure
{
public:
    virtual bool update() = 0;
    virtual bool setInput(uint32 index, Data* inputData) = 0;
    virtual bool setOutput(uint32 index, Data* inputData) = 0;
    virtual ~Procedure(){};
};



// --------------------------------------------------------- Pipeline components

class PipelineComponent
{
    virtual string name() const = 0;
};

class PipelineUpdater : public PipelineComponent
{
public:
    virtual bool update( Pipeline* p, uint32 flags ) = 0;
    virtual ~PipelineUpdater() {}
};

class PipelineRuleSet : PipelineComponent
{
public:
    virtual bool check( Pipeline* p ) = 0;

    virtual ~PipelineRuleSet() {}
};

class PipelineOptimizer : PipelineComponent
{
public:
    /**
     * Optimizes the pipeline.
     */ 
    virtual Procedure* optimize( Pipeline* p, uint32 flags ) = 0;
    /**
     * returns all the supported optimize flags
     */ 
    virtual uint32 modes() = 0;

    virtual ~PipelineOptimizer() {}
};





/**
 * Node based pipeline. Groups nodes and takes care of ordering
 *
 */ 
class Pipeline : public Procedure
{
public:
    typedef std::vector<Node*> NodeArray;
    typedef uint32 ID; 

    // update flags
    enum{ LAZY = 1, STEPBYSTEP = 2 };
    // optimize flags
    enum{ SPEED = 1, MEMORY = 2 };

    /**
     * Constructor.
     */ 
    Pipeline( PipelineUpdater* p_updater
        , PipelineOptimizer*   p_optimizer
        , PipelineRuleSet*     p_rules )
    : _updater(p_updater), _optimizer( p_optimizer ), _rules( p_rules )
    {
        _id = _newId();
    }

    /**
     * Updates the nodes in a correct order (eventually in parallel) using a
     * PipelineUpdater.
     *
     * Returns false in case of error. 
     */ 
    bool update(uint32 flags)
    {
        if(_updater)
            return _updater->update(this, flags);
        return false;
    }

    /**
     * Updates without flags (inherited from Procedure).
     */ 
    bool update() // override
    {
        return update(0);
    }

    /**
     * Creates a Procedure object that can execute the same actions that this
     * pipeline in a more optimized way.
     *
     * The optimization is performed by a PipelineOptimizer object and the nature
     * of the optimization is up to the PipelineOptimizer (though it can use hints
     * provided by the flags parameter).
     */ 
    Procedure* optimize(uint32 flags)
    {
        if(_optimizer)
            return _optimizer->optimize(this, flags);

        return 0;
    }

    /**
     * Returns this pipeline's nodes in a vector. 
     */
    const NodeArray& nodes()
    {
        return _nodes;
    }

    bool setInput(uint32 index, Data* inputData); // override
    bool setOutput(uint32 index, Data* inputData); // override
    
    
    bool addNode( Node* n );
    bool removeNode( Node* n );
    bool removeAllNodes();
    bool contains(const Node* n);

    ID id() const
    {
        return _id;
    }

    ~Pipeline();

protected:
    void setNodePipeline(Node* n, Pipeline* p);
private:
    static ID _newId()
    {
        static ID nextId = 0;
        return ++nextId;
    }
    
    ID _id;
    NodeArray _nodes;
    // components
    PipelineUpdater*    _updater;
    PipelineOptimizer*  _optimizer;
    PipelineRuleSet*    _rules;
};

}//namespace
}//namespace

#endif
