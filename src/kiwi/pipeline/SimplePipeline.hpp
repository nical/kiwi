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

#ifndef KIWI_SIMPLEPIPELINE_HPP
#define KIWI_SIMPLEPIPELINE_HPP

#include "kiwi/core/Container.hpp"
#include "kiwi/core/Filter.hpp"
#include "kiwi/core/Commons.hpp"
#include "AbstractPipeline.hpp"

#include <list>

namespace kiwi{
namespace core{

/**
 * @class Pipeline
 * @brief A meta-Filter class
 * 
 * The Pipeline Class is designed 
 */ 	
class SimplePipeline : public AbstractPipeline
{
public:
	SimplePipeline();

	void process();

	bool contains(Node* node);
	
	bool add(Node* toAdd);
	
	bool remove(Node* toRemove);

	/**
	 * @brief Prepares the pipeline before execution.
	 * 
	 * isReady will return false and nbErrors() will be different from 0
	 * if an error occurs while updating.
	 * In this case these errors, they can be retrieved one by one, 
	 * calling popError().
	 */ 
	void update();
		
	/**
	 * @brief Returns the number of remaining errors since last update.
	 * 
	 * This value is decremented each time an error is poped using popError()
	 */ 	
	kiwi::uint32_t nbErrors();
	
	/**
	 * @brief Pops an error from the update error's fifo.
	 */ 
	kiwi::string popError();
	
	
	
protected:
	
	unsigned int index(unsigned int x, unsigned int y);
	int findFilter(Filter* filter);
	typedef std::pair< unsigned int, unsigned int> constraints;
	
private:
	std::list<Filter*> _filters;
	std::list<Container*> _containers;
	
	uint32_t _nbErrors;
	
};	

}//namespace core
}//namespace kiwi



#endif
