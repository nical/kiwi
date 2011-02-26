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
#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/ReaderPort.hpp"
#include "kiwi/core/WriterPort.hpp"

namespace kiwi{
namespace core{


class Filter : public Node
{
public:

	int nodeType() { return Node::FILTER; }; // TODO: DEPRECATED

	bool update(int) { process(); return true; } 

	/**
	 * Main entry point of the filter. This is the function you should override to perform
	 * whatever the filter is supposed to do.
	 */
	virtual void process() = 0;

	/**
	 * @brief Automatically publishes the Container's ports in this Filter's
	 * Reader output ports.
	 * 
	 * The child classes, if they override this method, *must* call their
	 * parent's method as the only feature that brings this class is in 
	 * here.
	 */ 
	void layoutChanged()
	{
		uint32_t nbWriters = nbWriterPorts();
		//ScopedBlockMacro(__scop, "CanonicalFilter::layoutChanged")
		for(uint32_t i = 0; i < nbWriters; ++i){
			if( writerPort(i).isConnected() ){
				if( !dataPort(i).isEnabled() ){
//					setPortEnabled(dataPort(i),true);
					portIndex_t outIndex = writerPort(i).connectedPort()->index();
					DataPort& op
						= writerPort(i).connectedPort()->node()->dataPort(outIndex);
					bindPort( dataPort(i), op );
				}
			}else{
				dataPort(i).disconnectReader();
				dataPort(i).disconnectWriter();
//				setPortEnabled(dataPort(i),false);	
			}
		}
	}


	/**
	 * @brief Allows to associate a Reader Output with a Writer Input port.
	 *
	 * Basically what it does is make the writer port aware that if it connects
	 * to a port, the associated reader should read the data that the writer 
	 * accesses.
	 */ 

	void associateWriterToDataPort(WriterPort& writer, DataPort& reader) const
	{
		writer.associateReaderPort( &reader );
	}
	

	Filter():Node()
	{
	}

	~Filter()
	{

	}

// ---------------------------------------------------------------------
protected:
	

	kiwi::string strCommand( const kiwi::string& command )
	{
		if(command == "process")
		{
			if( isReady() ){
				process();
				return kiwi::string("done");
			}else{
				return "not ready";
			}
		}
		else
		{
			return Node::strCommand( command );
		}
	}

// ---------------------------------------------------------------------
private:

};


}//namespace core
}//namespace kiwi


#endif
