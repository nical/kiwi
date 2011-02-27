#ifndef KIWI_NODEFACTORY_TEST_HPP
#define KIWI_NODEFACTORY_TEST_HPP


#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/Factory.hpp"
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
	
	kiwi::utils::NodeFactory factory;
	
	factory.registerClass(
		"A", kiwi::utils::FactoryDescriptor<kiwi::core::Node>(&__createA, "#Filter") 
	);
	
	factory.registerClass(
		"B", kiwi::utils::FactoryDescriptor<kiwi::core::Node>(&__createB, "#Filter") 
	);
	
	factory.registerClass(
		"C", kiwi::utils::FactoryDescriptor<kiwi::core::Node>(&__createC, "#Filter") 
	);
	
	kiwi::core::Node* tfa = factory.newObject("A");
	assert(tfa != 0);
	kiwi::core::Node* tfb = factory.newObject("B");
	assert(tfb != 0);
	kiwi::core::Node* tfc = factory.newObject("C");
	assert(tfc != 0);
	kiwi::core::Node* tfx = factory.newObject("unregistered filter");
	assert(tfx == 0);
	
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
