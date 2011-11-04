#ifndef KIWI_CORE_PIPELINE_HPP
#define KIWI_CORE_PIPELINE_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{

class Node;



class Pipeline
{
public:
    typedef uint32 ID; 

    Pipeline();    
    virtual ~Pipeline();

    virtual bool addNode(Node* n) = 0;
    virtual bool update() = 0;
    
    ID id()
    {
        return _id;
    }

protected:
    void setNodePipeline(Node* n, Pipeline* p);
private:
    static ID _newId()
    {
        static ID nextId = 0;
        return ++nextId;
    }
    ID _id;
};


}//namespace
}//namespace

#endif
