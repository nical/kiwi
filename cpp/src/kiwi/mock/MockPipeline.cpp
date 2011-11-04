
#include "kiwi/mock/MockPipeline.hpp"


namespace kiwi{
namespace mock{


core::Pipeline* NewMockPipeline()
{
    return new core::Pipeline(
        new MockPipelineUpdater
        , new MockPipelineOptimizer
        , new MockPipelineRuleSet
    );
}


}//namespace
}//namespace
