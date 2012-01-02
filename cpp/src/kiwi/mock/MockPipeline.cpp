
#include "kiwi/mock/MockPipeline.hpp"
#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace mock{


core::Pipeline* NewMockPipeline()
{
    return new core::Pipeline(
        &kiwi::DefaultContext()
        , new MockPipelineUpdater
        , new MockPipelineRuleSet
    );
}


}//namespace
}//namespace
