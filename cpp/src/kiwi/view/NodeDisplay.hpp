
#pragma once
#ifndef KIWI_VIEW_GL_PIPELINEDISPLAY_HPP
#define KIWI_VIEW_GL_PIPELINEDISPLAY_HPP


namespace kiwi{
namespace view{

class NodeView;

/**
 * class that implements the drawing part of the UI for nodes.
 *
 * For instance OpenGL draw calls.
 */ 
class NodeDisplay
{
public:
    virtual bool display( const NodeView& view ) = 0;
    virtual ~NodeDisplay() {}
};


}//namespace
}//namespace


#endif
