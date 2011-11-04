
#pragma once
#ifndef KIWI_VIEW_GL_PIPELINEDISPLAY_HPP
#define KIWI_VIEW_GL_PIPELINEDISPLAY_HPP


namespace kiwi{
namespace view{

class PipelineDisplay;

class PipelineView
{
public:
    bool display() const;
private:
    PipelineDisplay* _display;
};


}//namespace
}//namespace


#endif
