#pragma once
#ifndef KIWI_CORE_OPCONNECT_HPP
#define KIWI_CORE_OPCONNECT_HPP

namespace kiwi{
namespace core{

class InputPort;
class OutputPort;

/**
 * Defines an operator to connect ports.
 *
 * This is equivalent to calling output.connect( input ), but is more readable.
 */ 
bool operator >> (OutputPort& output, InputPort& input );

}//namespace
}//namespace

#endif
