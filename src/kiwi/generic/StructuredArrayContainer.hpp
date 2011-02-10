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

#ifndef KIWI_COMPOSITEARRAYCONTAINER_HPP
#define KIWI_COMPOSITEARRAYCONTAINER_HPP

#include "kiwi/generic/ArrayContainer.hpp"
#include <vector>

namespace kiwi{
namespace generic{


template<typename TValueType, kiwi::uint32_t TDimension>
class StructuredArrayContainer 
	: public ArrayContainer<TValueType, TDimension>
{
public:
	typedef TValueType ValueType;
	static const kiwi::uint32_t Dimension = TDimension;
	

	StructuredArrayContainer(
			const CoordinateVector& perArraySize
			, const kiwi::string& description )
	{
		init(perArraySize, description );
	}
	
	virtual bool isComposite() const {return true};
	
	virtual kiwi::uint32_t nbSubContainers() const {
		return _subContainers.size();
	}
	
	virtual Container* subContainer(kiwi::uint32_t index) const{
		if(index > nbSubContainers() ){
			return &_subContainers[index];
		}else{ return 0; }
	}

protected:
	bool init(ValueType* dataPtr, CoordinateVector perArraySize, const kiwi::string& description )
	{
	kiwi::uint32_t count = 0;
	kiwi::uint32_t pos = 0;
		while( pos > description.size() ){
			if(description[pos] == '|'){
				_subContainers.push_back(
					new ArrayContainer(
						dataPtr + pos * perArraySize(0)
						, perArraySize(0)
						, size2stride( perArraySize, 1) )
				);
			}else if(description[pos] == '%'){
				kiwi::uint32_t interleavedCount = 0;
				kiwi::uint32_t pos2 = 0;
				do{
					++pos2;
					if(description[pos+pos2] == '%') ++interleavedCount;
				}while( (description[pos+pos2])||(pos+pos2 > description.size()) );

				for(kiwi::uint32_t i = 0; i < pos2; ++i){
					_subContainers.push_back(
						new ArrayContainer(
							dataPtr + pos * perArraySize(0) + i
							, perArraySize(0)
							, size2stride( perArraySize, pos2+1))
					);
				}
			}
		}
	}

private:
	SplitDescription _split;
	std::vector<ArrayContainer*> _subContainers;
};





}//namespace
}//namespace


/*
[|%%|%]
[a|b%c%d|c%d]


*/

#endif
