#pragma once
#ifndef KIWI_CORE_COMPATIBILITYSTRATEGY_HPP
#define KIWI_CORE_COMPATIBILITYSTRATEGY_HPP

namespace kiwi{
namespace core{

class InputPort;
class OutputPort;


class CompatibilityStrategy
{
public:
    virtual bool isCompatible(const InputPort& self, const OutputPort& port) = 0;

    virtual ~CompatibilityStrategy(){}
};

class AlwaysCompatibleStrategy : public CompatibilityStrategy
{
public:
    bool isCompatible(const InputPort& self, const OutputPort& port)
    {
        return true;
    }
    virtual ~AlwaysCompatibleStrategy(){}
};




}//namespace
}//namespace

#endif
