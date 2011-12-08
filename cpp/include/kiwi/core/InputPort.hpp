#pragma once
#ifndef KIWI_CORE_INPUTPORT_HPP
#define KIWI_CORE_INPUTPORT_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Connect.hpp"
#include "kiwi/core/Data.hpp"
#include "kiwi/core/Connect.hpp"

#include <vector>

namespace kiwi{
namespace core{

class Node;
class OutputPort;
class CompatibilityStrategy;
class DataTypeInfo;

/**
 * Input port of a kiwi::core::Node.
 *
 * Can be connected to copatibles output ports.
 * Each input port accepts maximum one connection.
 *
 * Compatibility depends on the data type of the port, its access flags and
 * can optionally tuned using a CompatibilityStrategy object (TODO).
 */ 
class InputPort
{
friend bool kiwi::core::protocol::Connect(OutputPort&,InputPort&);
friend bool kiwi::core::protocol::Disconnect(OutputPort&,InputPort&);
public:
    typedef void (*FeedBackFunction)(uint32);

    InputPort(){}
    InputPort(Node* n, const DataTypeInfo* datatype, DataAccessFlags flags)
    : _node(n), _dataTypeInfo(datatype), _flags(flags), _connection(0)
    {

    }

    /**
     * Returns a pointer to the output port connected to this input if any.
     *
     * Returns a nil pointer if this input port is not connected.
     */ 
    OutputPort* connection() const
    {
        return _connection;
    }

    /**
     * Returns the node this port belongs to.
     */ 
    Node* node() const
    {
        return _node;
    }
    
    /**
     * Returns the name of this port.
     *
     * Warning may be removed in the future!
     */ 
    string name() const
    {
        KIWI_NOT_IMPLEMENTED("InputPort::Name");
    	return "error";
    }

    /**
     * Returns true if this port is connected.
     */ 
    bool isConnected() const
    {
    	return _connection != 0;
    }

    /**
     * Returns true if this port is connected to a specific output port.
     */ 
    bool isConnectedTo(const OutputPort& port)
    {
    	return _connection == &port;
    }

    /**
     * Returns true if this port has the OPTIONNAL flag.
     */ 
    bool isOptional() const
    {
        return _flags & OPT;
    }

    /**
     * Returns a pointer to this port runtime data type info.
     */ 
    const DataTypeInfo* dataType() const
    {
        return _dataTypeInfo;
    }

    /**
     * Connects to an output port if possible.
     *
     * @return true if connection suceeded, fals otherwise.
     */ 
    bool connect(OutputPort& port);
    // TODO !
    template<typename Callable> void asyncConnect(OutputPort& port, Callable outcome);
    /**
     * Disconnects from a specific output port.
     *
     * @return true if disconnection succeded, false if the port was not
     * connected to the specified output port. 
     */ 
    bool disconnect(OutputPort& port);
    // TODO !
    template<typename Callable> void asyncDisconnect(OutputPort& port, Callable outcome);

    /**
     * Disconnects this port.
     */ 
    bool disconnectAll();

    /**
     * returns true if this port is compatible with a given output port.
     *
     * This test is performed before each connection.
     */ 
    bool isCompatible( const OutputPort& port ) const;

    Data* data() const;

    template<typename T> T* dataAs() const
    {
        if ( data() == 0 )
            return 0;
        return data()->value<T>();
    }

protected:
    Node* _node;
    const DataTypeInfo* _dataTypeInfo;
    DataAccessFlags _flags;
    OutputPort* _connection;
    //CompatibilityStrategy* _compatibility;
};


// Will be changed for truly async system 
template<typename Callable>
void InputPort::asyncConnect(OutputPort& port, Callable outcome)
{
    outcome( protocol::Connect(port, *this) );
}

template<typename Callable>
void InputPort::asyncDisconnect(OutputPort& port, Callable outcome)
{
    outcome( protocol::Disconnect(port, *this) );
}


} //namespace
} //namespace


#endif
