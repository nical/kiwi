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
 * @file ImageContainer.hpp
 * @brief Header file for the cairo image container
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.1
 */

#pragma once


#ifndef KIWI_CAIROIMAGECONTAINER_HPP
#define KIWI_CAIROIMAGECONTAINER_HPP

#include <cairo.h>
#include "kiwi/generic/ArrayContainerInterface.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/core/Tags.hpp"


namespace kiwi{
namespace image{
namespace cairo{




/**
 * @brief 8bits per channel ARGB Image container powered by the cairo
 * graphic library.
 *
 * This Container is compatible with generic::ArrayReader and
 * generic::ArrayWriter.
 */
class RGBAImageContainer : public generic::AbstractArrayContainer<uint8_t, 2>
{
public:
	// ----------------------------------------- Constructors/destructor
	/**
	 * @brief Constructor (allocates the data).
	 */
	RGBAImageContainer(const generic::Point<uint32_t, 2>& size);

	/**
	 * @brief Constructor (use pre-allocated data).
	 */
	RGBAImageContainer(uint8_t* data, const generic::Point<uint32_t, 2>& size);

	/**
	 * @brief Destructor.
	 */
	~RGBAImageContainer();
	// ------------------------------------------- class specific metods

	/**
	 * @brief Returns this image's cairo context.
	 *
	 * This is specific to cairo's functionning.
	 */
	inline cairo_t* getContext();
	/**
	 * @brief Returns this image's cairo surface.
	 *
	 * This is specific to cairo's functionning.
	 */
	inline cairo_surface_t* getSurface();

	/**
	 * @brief Saves the surface into a .png file.
	 */
	void saveToPng(string path);

	/**
	 * @brief Returns the image's width.
	 */
	uint32_t width() const ;

	/**
	 * @brief Returns the image's height.
	 */
	uint32_t height() const ;




	// ----------------------------------- virtual method implementation
	/**
	 * @brief Returns a pointer to the first element of a given channel.
	 *
	 */
	uint8_t* const getDataPointer(portIndex_t index) const ;

	/**
	 * @brief Returns the increments or stride.
	 */
	generic::Point<uint32_t, 3> increments(portIndex_t index) const ;

	/**
	 * @brief Returns the size of each span.
	 */
	generic::Point<uint32_t, 2> spanSize() const ;

	Tags tags() const { return Tags("#RGBA"); }

	virtual bool hasSubData() const { return true; }
  virtual kiwi::uint32_t size() const {return spanSize()[0]*spanSize()[1];}
  virtual kiwi::uint32_t memoryEstimation() const {return size()*sizeof(kiwi::uint8_t)*4;}
	/**
	 * @brief Returns the port's type tags (#rgba8 and #array2char)
	 */
	Tags readerOutputTags(portIndex_t);

	/**
	 * @brief Returns the port's type tags (#rgba8 and #array2char)
	 */
	Tags writerOutputTags(portIndex_t);


protected:
	cairo_surface_t *_surface;
	cairo_t* _context;

};





} //namsepace
} //namsepace
} //namsepace


#endif
