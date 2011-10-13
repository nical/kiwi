#pragma once
#ifndef KIWI_CORE_OPCONNECT_HPP
#define KIWI_CORE_OPCONNECT_HPP

namespace kiwi{
namespace core{

class InputPort;
class OutputPort;

bool operator >> (OutputPort& output, InputPort& input );

}//namespace
}//namespace

#endif
