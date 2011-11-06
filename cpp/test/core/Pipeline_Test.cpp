
#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/processing/ProcessingPipelineUpdater.hpp"



using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::processing;

KIWI_DECLARE_CONTAINER(int,"Int");
KIWI_DECLARE_CONTAINER(float,"Float");


int main()
{
    KIWI_BEGIN_TESTING("kiwi::core::Pipeline")

    auto IntInfo = DataTypeManager::RegisterDataType("Int", &Newint);

    NodeLayoutDescriptor layout1;
    layout1.inputs =
    {
        { "in1", IntInfo, READ },
        { "in2", IntInfo, READ }
    };
    layout1.outputs =
    {
        { "out", IntInfo, READ }
    };

    Pipeline Pipeline( new ProcessingPipelineUpdater(), 0, 0 );
        
    return KIWI_END_TESTING
}
