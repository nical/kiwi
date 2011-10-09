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

class InputPort
{
friend bool kiwi::core::protocol::Connect(OutputPort&,InputPort&);
friend bool kiwi::core::protocol::Disconnect(OutputPort&,InputPort&);
public:


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
    	return _name;
    }

    bool isConnected() const
    {
    	return _connection != 0;
    }

    bool isConnectedTo(const OutputPort* port)
    {
    	return _connection == port;
    }

    bool connect(OutputPort& port);
    bool disconnect(OutputPort& port);
    bool disconnectAll();
    bool isCompatible( const OutputPort& port ) const;

protected:
    Node* _node;
    OutputPort* _connection;
    string _name;
    DataAccessFlags _flags;
    CompatibilityStrategy* _compatibility;
};




} //namespace
} //namespace


#endif
