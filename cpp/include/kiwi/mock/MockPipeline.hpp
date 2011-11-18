
#pragma once
#ifndef KIWI_MOCK_MOCKPIPELINE_HPP
#define KIWI_MOCK_MOCKPIPELINE_HPP

#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace mock{

class MockPipelineUpdater : public core::PipelineUpdater
{
public:
    string name() const
    {
        return "MockPipelineUpdater";
    }
    bool update( core::Pipeline* p, uint32 flags )
    {
        return p != 0;
    }
};


class MockPipelineOptimizer : public core::PipelineOptimizer
{
public:
    string name() const
    {
        return "MockPipelineOptimizer";
    }
    /**
     * Does nothing.
     */ 
    core::Procedure* optimize( core::Pipeline* p, uint32 flags )
    {
        return 0;
    }

    /**
     * returns all the supported optimize flags (none)
     */ 
    virtual uint32 modes()
    {
        return 0;
    }
};

class MockPipelineRuleSet : public core::PipelineRuleSet
{
public:
    string name() const
    {
        return "MockPipelineRuleSet";
    }
    bool check( core::Pipeline* p )
    {
        return p != 0;
    }
};

core::Pipeline* NewMockPipeline();

}//namespace
}//namespace

#endif
