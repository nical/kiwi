#pragma once
#ifndef KIWI_CORE_INPUTPORT_HPP
#define KIWI_CORE_INPUTPORT_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Connect.hpp"

#include <vector>

namespace kiwi{
namespace core{

class Node;
class OutputPort;
class CompatibilityStrategy;
class DataTypeInfo;

class InputPort
{
friend bool kiwi::core::protocol::Connect(OutputPort&,InputPort&);
friend bool kiwi::core::protocol::Disconnect(OutputPort&,InputPort&);
public:

    InputPort(){}
    InputPort(Node* n, const DataTypeInfo* datatype, DataAccessFlags flags)
    : _node(n), _dataTypeInfo(datatype), _flags(flags), _connection(0)
    {

    }
    
    OutputPort* connection() const
    {
        return _connection;
    }

    Node* node() const
    {
        return _node;
    }
    string name() const
    {
    	return "error";
    }

    bool isConnected() const
    {
    	return _connection != 0;
    }

    bool isConnectedTo(const OutputPort& port)
    {
    	return _connection == &port;
    }

    bool isOptional() const
    {
        return _flags & OPTIONAL;
    }

    const DataTypeInfo* dataType() const
    {
        return _dataTypeInfo;
    }

    bool connect(OutputPort& port);
    bool disconnect(OutputPort& port);
    bool disconnectAll();
    bool isCompatible( const OutputPort& port ) const;

protected:
    Node* _node;
    DataAccessFlags _flags;
    const DataTypeInfo* _dataTypeInfo;
    OutputPort* _connection;
    //CompatibilityStrategy* _compatibility;
};




} //namespace
} //namespace


#endif
