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
#include "generic/AbstractArrayContainer.hpp"
#include "generic/Point.hpp"



namespace kiwi
{
namespace image
{
namespace cairo
{	




/**
 * @brief 8bits per channel ARGB Image container powered by the cairo 
 * graphic library.
 * 
 * This Container is compatible with generic::ArrayReader and 
 * generic::ArrayWriter.
 */ 
class ARGBImageContainer : public generic::AbstractArrayContainer<uint8_t, 2>
{
public:
	ARGBImageContainer(const generic::Point<uint32_t, 2>& size);
	~ARGBImageContainer();
	// ------------------------------------------- class specific metods
	
	/**
	 * @brief Returns's this image's context.
	 * 
	 * This is specific to cairo's functionning.
	 */ 
	inline cairo_t* getContext();
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
	
	
	
protected:
	cairo_surface_t *_surface;
	cairo_t* _context;

};





} //namsepace
} //namsepace
} //namsepace


#endif
