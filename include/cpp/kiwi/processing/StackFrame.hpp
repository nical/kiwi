
#ifndef KIWI_PROCESSING_STACKFRAME_HPP
#define KIWI_PROCESSING_STACKFRAME_HPP

#include <vector>
#include "stdint.h"

namespace kiwi {
namespace processing {

class StackFrame {
public:
    typedef int DataIndex;

    void* getData(DataIndex idx) {
        return _data[idx];
    }

    std::vector<void*> _data;
};

} // namespace
} // namespace

#endif
