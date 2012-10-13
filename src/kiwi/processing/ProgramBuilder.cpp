
#include "kiwi/processing/ProgramBuilder.hpp"
#include "kiwi/core/NodeGroup.hpp"
#include "kiwi/core/Node.hpp"

#include <map>

using namespace kiwi::core;
using namespace std;

namespace kiwi {
namespace processing {

class StackFrame;

typedef std::list<const Node*> NodeList;

namespace {
    void sortNodes(const Node* n, NodeList& outList)
    {
        if (n->flags() != Node::STANDARD) {
            return;
        }
        auto it = outList.begin();
        auto stop = outList.end();
        bool found = false;
        for (;it != stop; ++it) {
            if (*it == n) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::list<const Node*> prevs;
            n->previousNodes(prevs);
            auto pi = prevs.begin();
            auto ps = prevs.end();
            for (; pi!=ps; ++pi) {
                sortNodes(*pi, outList);
            }
            outList.push_back(n);
        }
    }

    struct DataIndexRef {
        int index;
        DataIndexRef* next;

        DataIndexRef(int idx) : index(idx), next(nullptr) {}

        DataIndexRef* get(int idx) {
            DataIndexRef* res = this;
            while (idx > 0) {
                res = res->next;
            }
            return res;
        }
    };

    void addDataIndexRef(const Node* n, int idx) {
/* TODO
        if (n->userData() == nullptr) {
            n->setUserData(new DataIndexRef(idx));
            return;
        }
        DataIndexRef* di = (DataIndexRef*) n->userData();
        while (di->next != nullptr) {
            di = di->next; 
        }
        di->next = new DataIndexRef(idx);
*/
    }

    int refCnt(vector<int>& stackDataRefCnt, int idx) {
        return stackDataRefCnt[idx];
    }

    int getAvailableIndex(vector<int>& stackDataRefCnt) {
        for (int i : stackDataRefCnt) {
            if (i == 0) return i;
        }
        stackDataRefCnt.push_back(1);
        return stackDataRefCnt.size() - 1;
    }

    void releaseRef(vector<int>& stackDataRefCnt, int idx) {
        if (--stackDataRefCnt[idx] == 1) {
            stackDataRefCnt[idx] = 0;
        }
    }

} // anonymous namespace



bool buildProcessingProgram(NodeGroup* ng, StackFrame* result)
{
    if (!ng || !result) return false;

    NodeList sortedNodes;
    NodeList outputNodes;

    ng->findAll(&isOutputNode, outputNodes);
    for (const Node* it : outputNodes) {        
        sortNodes(it, sortedNodes);
    }

    vector<int> stackDataRefCnt;
    std::map<NodeID, DataIndexRef*> dir;

    for (const Node* it : sortedNodes) {
        for (int o = 0; o < it->outputCount(); ++o) {
            int nConnections = it->outputPort(o).connectionCount();
            int idx = getAvailableIndex(stackDataRefCnt);
            stackDataRefCnt[idx] += nConnections;
            for (int c = 0; c < nConnections; ++c) {
                addDataIndexRef(it->outputLink(o,c)->inputNode(), idx);
            }
        }

        //DataIndexRef* refs = (DataIndexRef*) it->userData();
        DataIndexRef* refs = dir[it->id()];
        while (refs != nullptr) {
            releaseRef(stackDataRefCnt, refs->index);
            refs = refs->next;
        }
    }

    return true;
}

} // namespace
} // namespace
