
#ifndef KIWI_PROCESSING_OPERATION_HPP
#define KIWI_PROCESSING_OPERATION_HPP

#include <string>
#include <vector>

namespace kiwi {
namespace processing {

typedef int DataIndex;
typedef int32_t NodeID;

class OperationDebugInfo;
class StackFrame;

class OperationDebugInfo
{
public:
    std::string name;
    NodeID _nodeID;
};

class Operation {
public:
    Operation(OperationDebugInfo* dbg = nullptr) : _debugInfo(dbg) {}
    virtual ~Operation() { delete _debugInfo; }
    
    virtual void process(StackFrame* s) = 0;
    
    inline DataIndex getDataIndex(int i) {
        return _data[i];
    }

protected:
    std::vector<DataIndex> _data;
private:
    Operation* _next;
    OperationDebugInfo* _debugInfo;
};

} // namespace
} // namespace

#endif
