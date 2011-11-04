
#include "kiwi/core/PipelineManager.hpp"
#include "kiwi/core/Pipeline.hpp"


namespace kiwi{
namespace core{

PipelineManager::PipelineManager()
{

}

PipelineManager::~PipelineManager()
{

}

bool PipelineManager::addPipeline(Pipeline* p)
{
    _pipelines.push_back( p );
}

bool PipelineManager::updatePipeline( PipelineId id )
{
    for( auto it = _pipelines.begin(); it != _pipelines.end(); ++it  )
    {
        if( (*it)->id() == id )
            (*it)->update();
    }
}

bool PipelineManager::connect( PipelineId plid, NodeId nid1, uint32 outputPort, NodeId nid2, uint32 inputPort )
{
    Request r;
    r.type = Request::CONNECT;
    r.pipeline = plid;
    r.firstNode = nid1;
    r.secondNode = nid2;
    r.args[0] = outputPort;
    r.args[1] = inputPort;
    
    _requests.push( r );
}

bool PipelineManager::disconnect( PipelineId plid, NodeId nid, uint32 inputPort )
{
    Request r;
    r.type = Request::DISCONNECT;
    r.pipeline = plid;
    r.firstNode = nid;
    r.args[1] = inputPort;
    
    _requests.push( r );
}

bool PipelineManager::update()
{
    
}

}//namespace
}//namespace
