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

kiwi::core::Node* __createA(){ return new testFilterA; }
kiwi::core::Node* __createB(){ return new testFilterB; }
kiwi::core::Node* __createC(){ return new testFilterC; }

void FactoryTest()
{
ScopedBlockMacro(__scop, "kiwi::NodeFactory::Test")
	
	kiwi::core::NodeFactory factory;
	
	factory.registerNode(
		"A", kiwi::core::Descriptor<kiwi::core::Node>("testFilterA", &__createA, "#Filter") 
	);
	
	factory.registerNode(
		"B", kiwi::core::Descriptor<kiwi::core::Node>("testFilterB", &__createB, "#Filter") 
	);
	
	factory.registerNode(
		"C", kiwi::core::Descriptor<kiwi::core::Node>("testFilterB", &__createC, "#Filter") 
	);
	
	kiwi::core::Node* tfa = factory.newNode("A");
	assert(tfa != 0);
	kiwi::core::Node* tfb = factory.newNode("B");
	assert(tfb != 0);
	kiwi::core::Node* tfc = factory.newNode("C");
	assert(tfc != 0);
	kiwi::core::Node* tfx = factory.newNode("unregistered filter");
	assert(tfx == 0);
	
	//assert( factory.exFilterists("A") == kiwi::core::NodeFactory::FILTER);
	assert( factory.exists("A") );
	assert( !factory.exists("unregistered filter") );
	
	tfa->update();
	tfb->update();
	tfc->update();
	
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
