
#pragma once
#ifndef KIWI_CORE_PIPELINEMANAGER_HPP
#define KIWI_CORE_PIPELINEMANAGER_HPP

#include "kiwi/core/Commons.hpp"

#include <vector>
#include <queue>

namespace kiwi{
namespace core{

class Pipeline;

/**
 * Manage pipelines in a asynchronous way.
 */ 
class PipelineManager
{
public:
    typedef unsigned int PipelineId;
    typedef unsigned int NodeId;

    PipelineManager();
    ~PipelineManager();

    bool addPipeline(Pipeline* p);
    bool updatePipeline( PipelineId id );

    bool connect( PipelineId plid, NodeId nid1, uint32 outputPort, NodeId nid2, uint32 inputPort );
    bool disconnect( PipelineId plid, NodeId nid2, uint32 inputPort );

    bool update();
private:
    struct Request
    {
        enum { CONNECT, DISCONNECT, UPDATE } type;
        PipelineId pipeline;
        NodeId firstNode;
        NodeId secondNode;
        uint32 args[4];
    };
    typedef std::queue<Request> RequestQueue;
    typedef std::vector<Pipeline*> PipelineArray;

    PipelineArray  _pipelines;
    RequestQueue    _requests;
};

}//namespace
}//namespace

#endif
