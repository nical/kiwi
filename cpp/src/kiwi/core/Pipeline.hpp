#ifndef KIWI_CORE_PIPELINE_HPP
#define KIWI_CORE_PIPELINE_HPP

namespace kiwi{
namespace core{

class Node;



class Pipeline
{
public:
    
    virtual bool addNode(Node* n) = 0;
    virtual bool update() = 0;
    
    virtual ~Pipeline();

protected:
    void setNodePipeline(Node* n, Pipeline* p);
};


}//namespace
}//namespace

#endif
