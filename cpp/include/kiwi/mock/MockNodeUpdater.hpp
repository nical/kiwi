
#pragma once
#ifndef KIWI_MOCK_NODEUPDATER_HPP
#define KIWI_MOCK_NODEUPDATER_HPP

#include "kiwi/core/NodeUpdater.hpp"

namespace kiwi{
namespace mock{

class MockNodeUpdater : public core::NodeUpdater
{
public:
    bool update(const core::Node& n)
    {
        ++updateCount;
        return true;
    }

    static int updateCount;
};

}//namespace
}//namespace

#endif
