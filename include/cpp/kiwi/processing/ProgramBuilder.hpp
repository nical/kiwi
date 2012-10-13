
#ifndef KIWI_PROCESSING_PROGRAMBUILDER_HPP
#define KIWI_PROCESSING_PROGRAMBUILDER_HPP

namespace kiwi {

namespace core {
    class NodeGroup;
} // namespace core

namespace processing {

class StackFrame;
class Operation;

bool buildProcessingProgram(kiwi::core::NodeGroup* ng, StackFrame* result);

} // namespace
} // namespace

#endif
