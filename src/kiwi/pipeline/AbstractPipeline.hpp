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

#ifndef KIWI_ABSTRACTPIPELINE_HPP
#define KIWI_ABSTRACTPIPELINE_HPP

#include "kiwi/core/Node.hpp"
#include "kiwi/core/Commons.hpp"


namespace kiwi
{
namespace core
{

/**
 * @class AbstractPipeline
 * @brief Interface of te meta-Filter classes.
 * 
 */ 	
class AbstractPipeline : public Filter
{
public:
	AbstractPipeline() : Filter() {}

	/**
	 * @brief Returns true if the Node has been added to this Pipeline.
	 */ 
	virtual bool contains(Node* node) = 0;
	
	/**
	 * @brief Adds a filter to this Pipeline.
	 */ 
	virtual bool add(Node* toAdd) = 0;
	
	/**
	 * @brief Removes the node from this Pipeline.
	 */ 
	virtual bool remove(Node* toRemove) = 0;
	
	/**
	 * @brief Prepares the pipeline before execution.
	 * 
	 * isReady will return false and nbErrors() will be different from 0
	 * if an error occurs while updating.
	 * In this case these errors, they can be retrieved one by one, 
	 * calling popError().
	 */ 
	virtual void update() = 0;
		
	/**
	 * @brief Returns the number of remaining errors since last update.
	 * 
	 * This value is decremented each tipe an error is poped()
	 */ 	
	virtual kiwi::uint32_t nbErrors() = 0;
	
	/**
	 * @brief Pops an error from the update error's fifo.
	 */ 
	virtual kiwi::string popError() = 0;
	
private:


};



}//namespace core
}//namespace kiwi



#endif
