module kiwi.processing.processor;

import kiwi.core.commons;
import kiwi.core.node;
import kiwi.core.data;
import kiwi.core.nodegroup;


class SequentialProcessor : NodeProcessor
{
    override bool update( NodeGroup group )
    {
        throw NotImplemented("SequentialProcessor.update");
    }

}



version(unittest)
{
    import kiwi.core.mock;
}
unittest
{
    auto n1 = NewMockNode(1,1);
    auto n2 = NewMockNode(1,1);
    auto n3 = NewMockNode(2,1);
    auto n4 = NewMockNode(1,1);
    n1.output() >> n3.input(0);
    n2.output() >> n3.input(0);
    n3.output() >> n4.input(0);

    auto g = new NodeGroup;
    g.recursiveAddNode(n1);
   
    auto pr = new SequentialProcessor;

    try{
        pr.update(g);
    }catch(NotImplementedYetException e){};
}
