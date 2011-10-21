
#include "kiwi/core/Node.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/Data.hpp"
#include "kiwi/core/CompatibilityStrategy.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/DataStrategy.hpp"
#include "kiwi/core/NodeUpdater.hpp"

namespace kiwi{
namespace core{

Node::Node(Pipeline* pipeline, const NodeTypeInfo* typeInfo)
{
    SCOPEDBLOCK("Node::constructor");
    _pipeline = pipeline;
    _type = typeInfo;
    if(pipeline) pipeline->addNode(this);
    _id = _newId();
    
    for(int i = 0; i < typeInfo->inputs().size(); ++i)
    {
        _inputs.push_back( new InputPort( this
                , typeInfo->inputs()[i].dataType()
                , typeInfo->inputs()[i].accessFlags() )
        );
    }
    
    for(int i = 0; i < typeInfo->outputs().size(); ++i)
    {
        _outputs.push_back( new OutputPort( this
                , new AutoDataStrategy( typeInfo->outputs()[i].dataType() )
                , typeInfo->outputs()[i].accessFlags() )
        );
    }
}

void Node::update()
{
    SCOPEDBLOCK("Node::update");
    if ( _type->updater() )
        _type->updater()->update(*this);
}

void Node::findPreviousNodes()
{
    _previousNodes.clear();
    for( auto it = _inputs.begin(); it != _inputs.end(); ++it )
        if ( (*it)->isConnected() )
        {
            bool found = false;
            for( auto itpn = _previousNodes.begin()
                ; itpn != _previousNodes.end(); ++itpn )
            {
                if( (*it)->connection()->node() == *itpn )
                    found = true;
            }
            if( !found )
            {
                _previousNodes.push_back( (*it)->connection()->node() );
            }
        }
}

void Node::findNextNodes()
{
    _nextNodes.clear();
    for( auto it = _outputs.begin(); it != _outputs.end(); ++it )
        if ( (*it)->isConnected() )
        {
            for( auto itc = (*it)->connections().begin(); itc != (*it)->connections().begin(); ++itc )
            {
                bool found = false;
                for( auto itnn = _nextNodes.begin(); itnn != _nextNodes.end(); ++itnn )
                {
                    if( (*itc)->node() == *itnn )
                        found = true;
                }
                if( !found )
                {
                    _nextNodes.push_back( (*itc)->node() );
                }
            }
        }
}

void Node::inputConnected(InputPort* port, OutputPort* to)
{
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
        log << "added previous node" << endl;
    }
}

void Node::inputDisconnected(InputPort* port, OutputPort* from)
{
    Node* n = from->node();
    if ( n == 0 ) return;
    // look for the node in the input connections
    for( auto it = _inputs.begin(); it != _inputs.end(); ++it )
    {
        if ( (*it)->node() == n )
            return;
    }
    // not found, means it has to be removed from the prvious nodes list
    log << "have to remove previous node" << endl;
    for( int i = 0; i < _previousNodes.size(); ++i )
    {
        if( _previousNodes[i] == n )
        {
            _previousNodes[i] = _previousNodes[_previousNodes.size()-1];
            _previousNodes.resize(_previousNodes.size()-1);
            log << "removed previous node" << endl;
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
        log << "added next node" << endl;
    }
}
void Node::outputDisconnected(OutputPort* port, InputPort* from)
{
    Node* n = from->node();
    if ( n == 0 ) return;
    // look for the node in the output connections
    for( auto itp = _outputs.begin(); itp != _outputs.end(); ++itp )
    {
        for( auto itc = (*itp)->connections().begin(); itc != (*itp)->connections().end(); ++itc )
        {
            if ( (*itc)->node() == n )
            return;
        }
    }
    log << "have to remove next node" << endl;
    // not found, means it has to be removed from the prvious nodes list
    for( int i = 0; i < _nextNodes.size(); ++i )
    {
        if( _nextNodes[i] == n )
        {
            _nextNodes[i] = _nextNodes[_nextNodes.size()-1];
            _nextNodes.resize(_nextNodes.size()-1);
            log << "removed next node" << endl;
            return;
        }
    }
}


}//namespace
}//namespace
