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
#ifdef undefinedcrap


#pragma once

#ifndef KIWI_ARRAYDATA_HPP
#define KIWI_ARRAYDATA_HPP

#include "core/Resource.hpp"

#include <boost/lexical_cast.hpp>

namespace kiwi
{
namespace generic
{



template<typename TValueType, unsigned int TDimension, unsigned int TComponents>
class ArrayData : public core::Resource
{
public:
	typedef TValueType ValueType;

	kiwi::string sType("array"
				+ boost::lexical_cast<kiwi::string>(TDimension)+"d_"
				+ types::str<TValueType>() );
		addWriterInputPort(sType, "Write Result");

	ArrayData()
	{
		for(unsigned i = 0; i < TComponents; ++i)
		addReaderOutputPort(sType, portName(i) );

	}
// --------------------------------------------------------- Overloading



// -----------------------------------------------------------------
	
	ValueType * const getRawPointer() const;
	
	inline unsigned int size() const {return _data.size();}
	inline unsigned int spanSize(unsigned int dimension);
	
protected:
	
	virtual kiwi::string portName(unsigned int index)
	{
		switch(index)
		{
			case 0 : { return "x"; }
			case 1 : { return "y"; }
			case 2 : { return "z"; }
			case 3 : { return "w"; }
			default : { return "#"; }
		}
	}


	vector<ValueType> _data;
	unsigned int _increments[TDimension+1];

};	





	
}//namespace	
}//namespace	

#include "ArrayData.ih"

#endif

#endif //temporary
