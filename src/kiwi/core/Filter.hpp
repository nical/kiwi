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


/**
 * @file Filter.hpp
 * @brief Header file for the Filter class.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.2
 */


#pragma once

#ifndef KIWI_FILTER_HPP
#define KIWI_FILTER_HPP

#include "kiwi/core/Node.hpp"


namespace kiwi
{
namespace core
{

	
class Filter : public Node
{
public:

	int nodeType() { return Node::FILTER; };

	/**
	 * Main entry point of the filter. This is the function you should override to perform
	 * whatever the filter is supposed to do.
	 */ 
	virtual void process() = 0;

	
	/**
	 * @brief Returns true if the Filter is reday to process.
	 * 
	 * This method should be called before calling process().It checks that the boolean 
	 * readiness state is true AND that the optionnal readyCondition returns true as well.
	 * @see Node::readyCondition()
	 */ 
	bool isReady() {return (_ready && readyCondition() );}
	

	Filter():Node()
	{
		setReady(true);
	}

	~Filter()
	{
		
	}

// ---------------------------------------------------------------------	
protected:
	/**
	 * @brief a method to overload when there is need to test things when checking readiness
	 * 
	 * This method may optonally be overloaded in some case when it is convenient to 
	 * add an extra condition for checking wether the Filter is ready to compute.
	 * This is called within isReady() and does not replace setting the ready state with
	 * void setReady(bool), isReady checks that boths conditions are fulfilled.
	 * 
	 * by default returns true so that it doesn't interfere with setReady(bool) when the 
	 * method is not overloaded
	 */ 
	virtual bool readyCondition() {return true;} 
	
	/**
	 * @brief set a state of the Filter.
	 * 
	 * Partially set the "readiness" state of this Filter.
	 * Note that if readyCondition() is overloaded, both readyCondition and the readiness
	 * state must be true for isReady() to return true.
	 * 
	 */ 
	void setReady(bool state) {_ready = state;}

// ---------------------------------------------------------------------
private:
	bool _ready;

};


}//namespace core
}//namespace kiwi


#endif
