#pragma once

#ifndef KIWI_ArrayData_HPP
#define KIWI_ArrayData_HPP

#include "core/Resource.hpp"


namespace kiwi
{
namespace image
{



template<typename TValueType>
class ArrayData : public core::Resource
{
public:

// --------------------------------------------------------- Overloading
	/**
	 *	@brief Allocates a new Reader that is to be passed to an other Resource.
	 *
	 * Allocates a new Reader that is to be passed to an other Resource.
	 * This method should be implemented by every Resource/Filter.
	 * 
	 * 	@param index The index of the output port that to which corresponds the requested Reader.
	 *	@return A pointer to the Reader allocated by this method 
	 */ 
	core::Reader* newReader(unsigned index);

	/**
	 *	@brief Allocates a new Reader that is to be passed to an other Resource
	 *
	 * Allocates a new Reader that is to be passed to an other Resource.
	 * This method should be implemented by every Resource/Filter.
	 * 
	 * 	@param index The index of the output port that to which corresponds the requested Reader.
	 *	@return A pointer to the Reader allocated by this method 
	 */ 
	core::Writer* newWriter(unsigned index);

	/**
	 * @brief Verifies the compatibility of a given Reader to one of the input ports
	 *
	 * Returns true if the Reader passed in parameter is compatible with the input ports, by trying
	 * to downcast it.
	 * This method must be implemented by every Resource/Filter.
	 *
	 * @param inputIndex The index of the input port concerned
	 * @param reader A pointer to the Reader that is to be checked.
	 */
	bool isReaderCompatible(portIndex_t inputIndex, Reader* reader) const;

	/**
	 * @brief Verifies the compatibility of a given Writer to one of the input ports
	 *
	 * Returns true if the Writer passed in parameter is compatible with the input ports, by trying
	 * to downcast it.
	 * This method must be implemented by every Resource/Filter.
	 *
	 * @param inputIndex The index of the input port concerned
	 * @param writer A pointer to the Writer that is to be checked.
	 */
	bool isWriterCompatible(portIndex_t inputIndex, Writer* reader) const;


protected:

vector<ValueType> _data;
	
};	



	
}//namespace	
}//namespace	

#include "ArrayData.ih"

#endif
