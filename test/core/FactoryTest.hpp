// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#ifndef KIWI_NODEFACTORY_TEST_HPP
#define KIWI_NODEFACTORY_TEST_HPP



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
		"A", Descriptor<Filter>("testFilterA", &__createA, "#Filter") 
	);
	
	factory.registerNode(
		"B", Descriptor<Filter>("testFilterB", &__createB, "#Filter") 
	);
	
	factory.registerNode(
		"C", Descriptor<Filter>("testFilterB", &__createC, "#Filter") 
	);
	
	kiwi::core::Filter* tfa = factory.newFilter("A");
	assert(tfa != 0);
	kiwi::core::Filter* tfb = factory.newFilter("B");
	assert(tfb != 0);
	kiwi::core::Filter* tfc = factory.newFilter("C");
	assert(tfc != 0);
	kiwi::core::Filter* tfx = factory.newFilter("unregistered filter");
	assert(tfx == 0);
	
	tfa->process();
	tfb->process();
	tfc->process();
	
	delete tfa;
	delete tfb;
	delete tfc;
}

#endif
