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

/**
 * Mother class for pipeline components. 
 */ 
class PipelineComponent
{
public:
    typedef enum { UPDATER, OPTIMIZER, RULESET, OTHER } ComponentType;
    virtual ComponentType type() const = 0;
    virtual ~PipelineComponent() {}
};

/**
 * Mother class for pipeline updater components.
 *
 * Handles the update of a pipeline.
 */ 
class PipelineUpdater : public PipelineComponent
{
public:
    virtual bool update( Pipeline* p, uint32 flags ) = 0;
    PipelineComponent::ComponentType type() const
    { return PipelineComponent::UPDATER; }
};

/**
 * Mother class for pipeline rule set components
 *
 * Allows to add syntactic constraints to a pipeline.
 * This feature is not yet fully implemented. 
 */ 
class PipelineRuleSet : PipelineComponent
{
public:
    virtual bool check( Pipeline* p ) = 0;
    PipelineComponent::ComponentType type() const
    { return PipelineComponent::RULESET; }
};

/**
 * Mother class for pipeline optimizer components.
 *
 * Pipeline optimizers can generate an optimized version of the pipeline that
 * cannot be modified anymore, but should be more efficient.
 * The nature of the improvement is up to the optimizer implementation, though it
 * can optionally use the flag passed in parameter as a hint.
 */ 
class PipelineOptimizer : PipelineComponent
{
public:
    enum { NONE = 0, SPEED = 1, MEMORY = 2 };
    /**
     * Optimizes the pipeline.
     */ 
    virtual Procedure* optimize( Pipeline* p, uint32 flags ) = 0;
    /**
     * returns all the supported optimize flags
     */ 
    virtual uint32 modes() = 0;

    PipelineComponent::ComponentType type() const
    { return PipelineComponent::OPTIMIZER; }
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
    Pipeline( Context* ctx = &kiwi::DefaultContext()
        , PipelineUpdater* p_updater = 0
        , PipelineRuleSet*     p_rules =0 )
    : _context(ctx), _updater(p_updater), _rules( p_rules )
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
     * Returns this pipeline's nodes in a vector. 
     */
    const NodeArray& nodes()
    {
        return _nodes;
    }

    /**
     * TODO
     */ 
    bool setInput(uint32 index, Data* inputData); // override

    /**
     * TODO
     */ 
    bool setOutput(uint32 index, Data* inputData); // override
    
    /**
     * Adds a node to this pipeline.
     */ 
    bool addNode( Node* n );

    /**
     * Remove a given node from this pipeline without deleting it.
     */ 
    bool removeNode( Node* n );

    /**
     * Remove all nodes from this pipeline withou deleting them.
     */ 
    bool removeAllNodes();

    /**
     * Returns true if this pipeline contains a given node.
     */ 
    bool contains(const Node* n);

    Node * instanciateNode(const string& name);

    /**
     * Returns a pointer to the kiwi::core::Context used by this pipeline.
     */ 
    Context * context() const
    {
        return _context;
    }

    /**
     * Returns the unique id of the pipeline object.
     */ 
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
    Context*            _context;
    PipelineUpdater*    _updater;
    PipelineRuleSet*    _rules;

};

}//namespace
}//namespace

#endif
