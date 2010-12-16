#ifndef KIWI_NODEFACTORY_TEST_HPP
#define KIWI_NODEFACTORY_TEST_HPP


#include "kiwi/core/Commons.hpp"
#include "kiwi/core/NodeFactory.hpp"
#include "kiwi/core/Filter.hpp"


class testFilterA : public kiwi::core::Filter
{
public:
	void process()
	{
	ScopedBlockMacro(__scop,"testFilterA::process")
	}
};
class testFilterB : public kiwi::core::Filter
{
public:
	void process()
	{
	ScopedBlockMacro(__scop,"testFilterB::process")
	}
};
class testFilterC : public kiwi::core::Filter
{
public:
	void process()
	{
	ScopedBlockMacro(__scop,"testFilterC::process")
	}
};

kiwi::core::Filter* __createA(){ return new testFilterA; }
kiwi::core::Filter* __createB(){ return new testFilterB; }
kiwi::core::Filter* __createC(){ return new testFilterC; }

void FactoryTest()
{
ScopedBlockMacro(__scop, "kiwi::NodeFactory::Test")
	
	kiwi::core::NodeFactory factory;
	
	factory.registerNode(
		"A", kiwi::core::Descriptor<kiwi::core::Filter>("testFilterA", &__createA, "#Filter") 
	);
	
	factory.registerNode(
		"B", kiwi::core::Descriptor<kiwi::core::Filter>("testFilterB", &__createB, "#Filter") 
	);
	
	factory.registerNode(
		"C", kiwi::core::Descriptor<kiwi::core::Filter>("testFilterB", &__createC, "#Filter") 
	);
	
	kiwi::core::Filter* tfa = factory.newFilter("A");
	assert(tfa != 0);
	kiwi::core::Filter* tfb = factory.newFilter("B");
	assert(tfb != 0);
	kiwi::core::Filter* tfc = factory.newFilter("C");
	assert(tfc != 0);
	kiwi::core::Filter* tfx = factory.newFilter("unregistered filter");
	assert(tfx == 0);
	
	assert( factory.exists("A") == kiwi::core::NodeFactory::FILTER);
	assert( factory.exists("A") );
	assert( !factory.exists("unregistered filter") );
	
	tfa->process();
	tfb->process();
	tfc->process();
	
	delete tfa;
	delete tfb;
	delete tfc;
}

#ifdef KIWI_TEST_MAIN

int main()
{
	FactoryTest();
	return 0;
}

#endif

#endif
