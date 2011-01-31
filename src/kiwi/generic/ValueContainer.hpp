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

#ifndef KIWI_GENERIC_VALUE_HPP
#define KIWI_GENERIC_VALUE_HPP

#include "kiwi/generic/ValueContainerInterface.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/types.hpp"
#include "kiwi/core/NodeFactory.hpp"
#include "kiwi/core/Ports.hpp"

namespace kiwi{
namespace generic{



template<typename TValueType> class ValueReader;
template<typename TValueType> class ValueWriter;

// ------------------------------------------------------------ Container
template <typename TValueType>
class ValueContainer : public ValueContainerInterface<TValueType>
{
public:
	typedef TValueType ValueType;

	ValueContainer(ValueType init)	: _data(init)	{	}

	virtual ValueType getValue() const { return _data; }
	virtual void setValue(ValueType value) {_data = value;}

	static kiwi::core::Node* newValueContainer()
	{
		core::Node* newNode = new core::Node();
		newNode->addContainer( new ValueContainer<TValueType>(0), true, true );
		return newNode;
	}

	static void registerToFactory(kiwi::core::NodeFactory& factory, const kiwi::string& filterId)
	{
		kiwi::string tags("#Container#value#");
		kiwi::string name("ValueContainer<");
		tags += types::str<ValueType>();
		name += types::str<ValueType>();
		name += ">";

		factory.registerNode( filterId
				, kiwi::core::Descriptor<kiwi::core::Node>(
					name
					, newValueContainer
					, tags )
			);
	}

private:
	ValueType _data;
};



}//namespace
}

#endif
