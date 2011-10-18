#pragma once
#ifndef KIWI_CORE_OUTPUTPORT_HPP
#define KIWI_CORE_OUTPUTPORT_HPP

#include <vector>
#include "kiwi/core/Connect.hpp"
#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{

class Node;
class Data;
class DataTypeInfo;
class InputPort;
class DataStrategy;


class OutputPort
{
friend bool kiwi::core::protocol::Connect(OutputPort&,InputPort&);
friend bool kiwi::core::protocol::Disconnect(OutputPort&,InputPort&);
public:
    typedef std::vector<InputPort*> ConnectionArray;

    //OutputPort(){}
    /**
     * Constructor.
     */ 
    OutputPort(Node* n, DataStrategy* datastrategy, DataAccessFlags flags = READ|WRITE)
    :_node(n), _dataStrategy(datastrategy), _accessFlags(flags)
    {
        
    }

    const ConnectionArray& connections() const
    {
        return _connections;
    }

    InputPort* connection(int index) const
    {
        return _connections[index];
    }

    Node* node() const
    {
        return _node;
    }

    Data* data() const;
    
    const DataTypeInfo* dataType() const;
    
    DataAccessFlags accessFlags() const
    {
        return _accessFlags;
    }

    bool connect( InputPort& port );
    bool disconnect( InputPort& port );
    bool disconnectAll();

    bool isCompatible(const InputPort& port) const;
    

    bool hasDataStrategy() const
    {
        return _dataStrategy != 0;
    }

    bool isConnected() const
    {
    	return _connections.size() != 0;
    }

    bool isConnectedTo( const InputPort& port )
    {
    	for(int i = 0; i < _connections.size(); ++i)
    		if( &port == _connections[i] )
    			return true;
    	return false;
    }


protected://methods
    int _indexOf(const InputPort& port)
    {
    	for(int i = 0; i < _connections.size(); ++i)
    		if(_connections[i] == &port)
    			return true;
    	return false;
    }
protected://variables
    Node* _node;
    ConnectionArray _connections;
    DataAccessFlags _accessFlags;
    DataStrategy* _dataStrategy;

};

} //namespace
} //namespace


#endif

