
#include "kiwi/processing/ProcessingPipelineUpdater.hpp"
#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Node.hpp"

using namespace kiwi::core;

namespace kiwi{
namespace processing{


bool ProcessingPipelineUpdater::update( Pipeline* p, uint32 flags )
{

    Pipeline::NodeArray toUpdate = p->nodes();
    
    int i = 0;
    while( toUpdate.size() > 0 )
    {
        log<< "#" <<i<<endl;
        Node* n = toUpdate[i];
        auto & dependencies = toUpdate[i]->previousNodes();
        // look for dependencies 
        bool foundDependency = false;
        for(auto it = dependencies.begin(); it!=dependencies.end();++it)
        {
            for(auto it2 = toUpdate.begin(); it2!=toUpdate.end(); ++it2)
                if(*it2 ==*it)
                {
                    foundDependency = true;
                    break;
                }
        }
        if( !foundDependency )
        {
            n->update();
            // then remove the node from toUpdate
            toUpdate[i] = toUpdate[ toUpdate.size()-1];
            toUpdate.resize(toUpdate.size()-1);
        }

        ++i;

        if( i >= toUpdate.size() ) i = 0;
    }
    
    
    return false;
}




}//Namespace
}//Namespace
