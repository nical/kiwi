
#pragma once
#ifndef KIWI_PROCESSING_PROCESSINGPIPELINE_HPP
#define KIWI_PROCESSING_PROCESSINGPIPELINE_HPP

namespace kiwi{
namespace core{
class Node;
}//namespace
}//namespace


namespace kiwi{
namespace processing{

class ProcessingPipeline : public core::Pipeline
{
public:
    typedef std::vector<core::Node*> NodeVector; 

    bool addNode(core::Node* n);
    bool update();

private:
    NodeVector _nodes;
};

}//namespace
}//namespace

#endif
