
#pragma once
#ifndef KIWI_VIEW_GL_PIPELINEDISPLAY_HPP
#define KIWI_VIEW_GL_PIPELINEDISPLAY_HPP

#include "kiwi/core/Pipeline.hpp"

namespace kiwi{
namespace view{

class PipelineDisplay;
class NodeView;

class PipelineView
{
public:
    typedef std::vector<NodeView*> NodeViewArray;
    bool display() const;

    NodeViewArray nodeViews() const
    {
        return _nodeViews;
    }
private:
    PipelineDisplay* _display;
    NodeViewArray _nodeViews;
};


}//namespace
}//namespace


#endif
