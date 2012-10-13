
#include <string>
#include <vector>
#include <stdint.h>

struct kiwi_Node;
struct kiwi_Link;
struct kiwi_NodeTypeInfo;
struct kiwi_NodeGroup;
typedef uint64_t kiwi_DataType;

struct kiwi_Link
{
    kiwi_Node* outptutNode;
    kiwi_Node* inptutNode;
    int        outptutPort;
    int        inptutPort;
};

struct kiwi_Node 
{
    std::vector< std::vector<kiwi_Link*> > inputs;
    std::vector< std::vector<kiwi_Link*> > outputs;
    kiwi_NodeTypeInfo* type;
    kiwi_NodeGroup* parent;
    char* name;
};

struct kiwi_PortDescriptor
{
    kiwi_DataType dataType;
    char*         name;
    uint32_t      flags;
};

struct kiwi_NodeLayoutDescriptor
{
    kiwi_PortDescriptor* inputs;
    kiwi_PortDescriptor* outputs;
    uint32_t nbInputs;
    uint32_t nbOutputs;
    char*    name;
};

struct kiwi_NodeTypeInfo
{
    kiwi_NodeLayoutDescriptor* layout;
    // the node's action.
    int engineID;
    void* userData;
};
