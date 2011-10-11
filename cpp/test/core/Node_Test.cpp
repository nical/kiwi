
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/processing/ProcessingPipeline.hpp"
#include "kiwi/mock/MockNodeUpdater.hpp"

using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::processing;

int main()
{
	KIWI_BEGIN_TESTING("Kiwi::core::Node Test");

    NodeInitializer nt1init("NodeTest1");
    nt1init.addPort("in", IN, 0);
    ProcessingPipeline p;

    Node::InputArray ins;
    Node::OutputArray outs;
    Node n1(&p, ins, outs, new mock::MockNodeUpdater );
    
	kiwi::log << "hej\n";
	
	return KIWI_END_TESTING;
}
