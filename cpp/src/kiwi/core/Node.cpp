
#include "kiwi/core/Node.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/Data.hpp"
#include "kiwi/core/CompatibilityStrategy.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/NodeUpdater.hpp"
#include "kiwi/view/NodeView.hpp"


#ifndef NDEBUG
static int _nodeCount = 0;
int kiwi_dev_GetNodeCount(){return _nodeCount;}
#endif

namespace kiwi{
namespace core{

Node::Node(Pipeline* pipeline, const NodeTypeInfo* typeInfo)
{
    SCOPEDBLOCK("Node::constructor");
    _view = 0;
    _pipeline = pipeline;
    _type = typeInfo;
    if(pipeline) pipeline->addNode(this);
    _id = _newId();
    
    for(uint32 i = 0; i < typeInfo->inputs().size(); ++i)
    {
        _inputs.push_back( new InputPort( this
                , typeInfo->inputs()[i].dataType()
                , typeInfo->inputs()[i].accessFlags() )
        );
    }
    
    for(uint32 i = 0; i < typeInfo->outputs().size(); ++i)
    {
        _outputs.push_back( new OutputPort( this
                //, new AutoDataStrategy( typeInfo->outputs()[i].dataType() )
                , DataProxy( typeInfo->outputs()[i].dataType()->newInstance() )
                , typeInfo->outputs()[i].dataType()
                , typeInfo->outputs()[i].accessFlags() )
        );
    }
#ifndef NDEBUG
    ++_nodeCount;
#endif
}

Node::~Node()
{
#ifndef NDEBUG
    --_nodeCount;
#endif
}

bool Node::update()
{
    SCOPEDBLOCK("Node::update");
    int outcome;
    if ( _type->updater() )
    {
        outcome = _type->updater()->update(*this);
        if(_view)_view->nodeUpdated(outcome);
        return outcome;
    }
    else
    {
        if(_view)_view->nodeUpdated(false);
        return false;
    }
}


void Node::inputConnected(InputPort* port, OutputPort* to)
{
    SCOPEDBLOCK("Node::inputConnected");
    Node* n = to->node();
    if ( n == 0 ) return;
    bool found = false;
    for( auto it = _previousNodes.begin(); it != _previousNodes.end(); ++it )
    {
        if ( (*it) == n )
        {
            found = true;
            break;
        }
    }
    if ( !found ){
        _previousNodes.push_back(n);
    }
    if( view() ) view()->inputConnected(port, to);
}

void Node::inputDisconnected(InputPort* port, OutputPort* from)
{
    log.debug() << "Node::inputDisconnected" << endl;
    
    if( view() ) view()->inputDisconnected(port, from); // TODO: maybe should be done last

    Node* n = from->node();
    if ( n == 0 ) return;
    // look for the node in the input connections
    for( auto it = _inputs.begin(); it != _inputs.end(); ++it )
    {
        if ( (*it)->node() == n )
            return;
    }
    // not found, means it has to be removed from the prvious nodes list
    for( uint32 i = 0; i < _previousNodes.size(); ++i )
    {
        if( _previousNodes[i] == n )
        {
            _previousNodes[i] = _previousNodes[_previousNodes.size()-1];
            _previousNodes.resize(_previousNodes.size()-1);
            return;
        }
    }
}

void Node::outputConnected(OutputPort* port, InputPort* to)
{
    Node* n = to->node();
    if ( n == 0 ) return;
    bool found = false;
    for( auto it = _nextNodes.begin(); it != _nextNodes.end(); ++it )
    {
        if ( (*it) == n )
        {
            found = true;
            break;
        }
    }
    if ( !found ){
        _nextNodes.push_back(n);
    }

    if( view() ) view()->outputConnected(port, to);
}

void Node::outputDisconnected(OutputPort* port, InputPort* from)
{
    // TODO: maybe should be done at the end of the function
    if( view() ) view()->outputDisconnected(port, from);
    
    Node* n = from->node();
    if ( n == 0 ) return;
    // look for the node in the output connections
    int i=0; int j=0;
    for( auto itp = _outputs.begin(); itp != _outputs.end(); ++itp )
    {
        for( auto itc = (*itp)->connections().begin(); itc != (*itp)->connections().end(); ++itc )
        {
            if ( (*itc)->node() == n )
            {
                return;
            }
            ++j;
        }
        ++i;
    }
    // not found, means it has to be removed from the prvious nodes list
    for( uint32 i = 0; i < _nextNodes.size(); ++i )
    {
        if( _nextNodes[i] == n )
        {
            _nextNodes[i] = _nextNodes[_nextNodes.size()-1];
            _nextNodes.resize(_nextNodes.size()-1);
            return;
        }
    }
}

const InputPort& Node::input( string portName ) const
{
    for(uint32 i = 0; i < inputs().size(); ++i)
    {
        if(_type->inputs()[i].name() == portName)
            return input(i);
    }
    assert("port not found" == portName );
    return input(0); // to avoid warnings, should never happen though
}

const OutputPort& Node::output( string portName ) const
{
    for(uint32 i = 0; i < outputs().size(); ++i)
    {
        if(_type->outputs()[i].name() == portName)
            return output(i);
    }
    assert("port not found" == portName );
    return output(0); // to avoid warnings, should never happen though
}

void Node::setView( view::NodeView * v )
{
    _view = v;
    _view->setNode(this);
}

string Node::inputName( uint32 i ) const
{
    return _type->inputs()[i].name();
}

string Node::outputName( uint32 i ) const
{
    return _type->outputs()[i].name();
}

uint32 Node::indexOf( const InputPort * p )
{
    for( uint32 i = 0; i < _inputs.size(); ++i )
        if( _inputs[i] == p)
            return i;
    log.error() << "Node::indexOf(InputPort*): bad param, return -1" << endl;
    return -1;
}

uint32 Node::indexOf( const OutputPort * p )
{
    for( uint32 i = 0; i < _outputs.size(); ++i )
        if( _outputs[i] == p)
            return i;
    log.error() << "Node::indexOf(OutputPort*): bad param, return -1" << endl;
    return -1;
}

}//namespace
}//namespace
