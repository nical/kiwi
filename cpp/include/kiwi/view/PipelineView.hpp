
#pragma once
#ifndef KIWI_VIEW_GL_PIPELINEDISPLAY_HPP
#define KIWI_VIEW_GL_PIPELINEDISPLAY_HPP

#include "kiwi/core/Pipeline.hpp"

namespace kiwi{ namespace core{ class Pipeline; }}

namespace kiwi{
namespace view{

class PipelineDisplay;
class NodeView;

class PipelineView
{
public:
    core::Pipeline * pipeline() const
    {
        return _pipeline;
    }
    
private:
    core::Pipeline* _pipeline;
};


}//namespace
}//namespace


#endif
