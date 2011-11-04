
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

}

bool PipelineManager::disconnect( PipelineId plid, NodeId nid2, uint32 inputPort )
{

}

}//namespace
}//namespace
