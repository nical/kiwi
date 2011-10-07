
#pragma once
#ifndef KIWI_CORE_CONNECT_HPP
#define KIWI_CORE_CONNECT_HPP

namespace kiwi{
namespace core{

class InputPort;
class OutputPort;

namespace protocol{


bool Connect( OutputPort& output, InputPort& input );
bool Disconnect( OutputPort& output, InputPort& input );


}//namespace
}//namespace
}//namespace

#endif
