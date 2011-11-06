
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
    layout1.inputs = {
        { "in0", IntInfo, READ },
        { "in1", IntInfo, READ }
    };
    layout1.outputs = {
        { "out0", IntInfo, READ },
        { "out1", IntInfo, READ }
    };

    Pipeline pipeline( new ProcessingPipelineUpdater(), 0, 0 );

    pipeline.update();
    
    return KIWI_END_TESTING
}
