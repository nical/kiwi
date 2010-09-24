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

#ifndef KIWI_AUDIOSAMPLEBUFFER_HPP
#define KIWI_AUDIOSAMPLEBUFFER_HPP

#include "core/Commons.hpp"
#include "generic/GenericIterator.hpp"
#include "generic/ArrayIterator.hpp"

#include "core/Resource.hpp"



#include <assert.h>

namespace kiwi
{
namespace audio
{


template<typename T>
class AudioSampleBuffer;

template<typename ValueTypeT>
class AudioSampleReader : public core::Reader
{
public:
	// typedefs
	typedef ValueTypeT ValueType;

	// methods
	AudioSampleReader(AudioSampleBuffer<ValueTypeT>* theResource)
	{
		assert(theResource != 0);
		_data = theResource->getRawPointer();
		_size = theResource->size();
	}
	/**
	 * Fast yet unsafe data access method
	 */ 
	inline ValueType* const getRawPointer() { return _data; }

	inline ValueType get(unsigned int pos) const { return _data[pos]; }

	inline unsigned int size() const { return _size; } 

protected:
	ValueType* _data;
	unsigned int _size;
	AudioSampleReader();
	
};

// ---------------------------------------------------------------------

template<typename ValueTypeT>
class AudioSampleWriter : public core::Writer
{
public:
	// typedefs
	typedef ValueTypeT ValueType;

	// methods
	AudioSampleWriter(AudioSampleBuffer<ValueTypeT>* theResource)
	{
		assert(theResource != 0);
		_data = theResource->getRawPointer();
		_size = theResource->size();
	}
	/**
	 * Fast yet unsafe data access method
	 */ 
	inline ValueType* const getRawPointer() {return _data;}

	inline ValueType get(unsigned int pos) const {return _data[pos];}
	inline ValueType set(ValueType val, unsigned int pos) const {return _data[pos];}

	inline unsigned int size() const { return _size; } 

protected:
	ValueType* _data;
	unsigned int _size;
	AudioSampleWriter();
	
};


// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

//template<typename T> class AudioSampleReader<T>;
//template<typename T> class AudioSampleWriter<T>;
//template<typename ValueTypeT>
//class AudioSampleWriter;
//template<typename ValueTypeT>
//class AudioSampleReader;


template<typename ValueTypeT>
class AudioSampleBuffer : public core::Resource
{
public:
	// typedefs
	typedef ValueTypeT ValueType;
	
	AudioSampleBuffer(ValueType* data, unsigned int size, bool reAllocate = true )
		: _size(size), _reAllocated(reAllocate)
	{
		if(reAllocate)
		{
			_data = new ValueType[size];
			for(unsigned int i = 0; i < size; ++i)
			{
				_data[i] = data[i];
			}
		}
		else
		{
			_data = data;
		}
	}
	
	//AudioSampleBuffer(const AudioSampleBuffer<ValueType>& buf );
	~AudioSampleBuffer();

	/**
	 * Fast yet unsafe data access method
	 */ 
	ValueType* const getRawPointer() {return _data;}

	/**
	 *	@brief Allocates a new Reader that is to be passed to an other Resource.
	 *
	 * Allocates a new Reader that is to be passed to an other Resource.
	 * This method should be implemented by every Resource/Filter.
	 * 
	 * 	@param index The index of the output port that to which corresponds the requested Reader.
	 *	@return A pointer to the Reader allocated by this method 
	 */ 
	core::Reader* newReader(unsigned int index);

	/**
	 *	@brief Allocates a new Reader that is to be passed to an other Resource
	 *
	 * Allocates a new Reader that is to be passed to an other Resource.
	 * This method should be implemented by every Resource/Filter.
	 * 
	 * 	@param index The index of the output port that to which corresponds the requested Reader.
	 *	@return A pointer to the Reader allocated by this method 
	 */
	core::Writer* newWriter(unsigned int index);

	/**
	 * @brief Verifies the compatibility of a given Reader to one of the input ports
	 *
	 * Returns true if the Reader passed in parameter is compatible with the input ports
	 * Here it always return false as there's no input ports
	 * This method must be implemented by every Resource/Filter.
	 *
	 * @param inputIndex The index of the input port concerned
	 * @param reader A pointer to the Reader that is to be checked.
	 */
	bool isReaderCompatible(portIndex_t inputIndex, core::Reader* reader) const {return false;}

	/**
	 * @brief Verifies the compatibility of a given Writer to one of the input ports
	 *
	 * Returns true if the Writer passed in parameter is compatible with the input ports.
	 * Here it always return false as there's no input ports
	 * This method must be implemented by every Resource/Filter.
	 *
	 * @param inputIndex The index of the input port concerned
	 * @param writer A pointer to the Writer that is to be checked.
	 */
	bool isWriterCompatible(portIndex_t inputIndex, core::Writer* reader) const {return false;}

	inline unsigned int size() const {return _size;}
	
protected:
	ValueType* _data;
	unsigned int _size;
	bool _reAllocated;

};



// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------






}
}

#include "AudioSampleBuffer.ih"

#endif
