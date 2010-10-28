//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#pragma once

#ifndef KIWI_FILTER_HPP
#define KIWI_FILTER_HPP

#include "Node.hpp"


namespace kiwi
{
namespace core
{

	
class Filter : public Node
{
public:

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
	
	
	/**
	 * Returns true. Overloaded from Node, this helps Pipeline know wether or not the
	 * Node they manipulate are filters.
	 */ 
	bool isAFilter() {return true;}


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
