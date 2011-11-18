
#pragma once

#ifndef KIWI_PROCESSING_PROCESSINGPIPELINEUPDATER
#define KIWI_PROCESSING_PROCESSINGPIPELINEUPDATER

#include "kiwi/core/Pipeline.hpp"

namespace kiwi{
namespace processing{

class ProcessingPipelineUpdater : public kiwi::core::PipelineUpdater
{
public:
    bool update( core::Pipeline* p, uint32 flags );
};

}//namespace
}//namespace

#endif
