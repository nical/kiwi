
#pragma once
#ifndef KIWI_VIEW_GL_PIPELINEDISPLAY_HPP
#define KIWI_VIEW_GL_PIPELINEDISPLAY_HPP


namespace kiwi{
namespace view{

class PipelineView;

class PipelineDisplay
{
public:
    virtual bool display( const PipelineView& pv ) = 0;
    virtual ~PipelineDisplay() {};
private:
};


}//namespace
}//namespace


#endif
