#pragma once


#ifndef KIWI_CAIROIMAGECONTAINER_HPP
#define KIWI_CAIROIMAGECONTAINER_HPP

#include <cairo.h>
#include "generic/AbstractArrayContainer.hpp"
#include "generic/Point.hp"



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
 * 
 */ 
class ARGBImageContainer : public genric::AbstractArrayContainer<uint8, 2>
{
public:
	ImageContainerARGB(const Point<unsigned int, 2>& size);
	~ARGBImageContainer();
	// ------------------------------------------- class specific metods
	
	inline cairo_t getContext();

	void saveToPng(string path);

	uint32_t width();
	uint32_t height();
	
	
	
	
	// ----------------------------------- virtual method implementation
	
	uint8_t* const getDataPointer(portIndex_t index) const ;
	
	/**
	 * Returns the increments or stride.
	 */ 
	Point<unsigned int, TDimension+1> increments(portIndex_t index) const ;
	
	/**
	 * Returns the size of each span.
	 */ 
	Point<unsigned int, TDimension> spanSize() const ;
	
	
	
protected:
	cairo_surface_t *_surface;
	cairo_t* _context;

};





} //namsepace
} //namsepace
} //namsepace

#endif
