

#include "ImageContainer.hpp"

namespace kiwi
{
namespace image
{
namespace cairo
{	

using namespace generic;

ARGBImageContainer::ARGBImageContainer(const generic::Point<uint32_t, 2>& size) 
: AbstractArrayContainer<uint8_t, 2>()
{			
	_surface = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32
		, size(0), size(1) );
		
	_context = cairo_create( _surface );
}


inline 
cairo_t* 
ARGBImageContainer::getContext() 
{ 
	return _context; 
}

inline 
cairo_surface_t* 
ARGBImageContainer::getSurface() 
{ 
	return _surface; 
}


void 
ARGBImageContainer::saveToPng(string path)
{
	cairo_surface_write_to_png( _surface, path.c_str() );
}

inline 
uint32_t 
ARGBImageContainer::width() const
{
	return cairo_image_surface_get_width( _surface );
}

inline 
uint32_t 
ARGBImageContainer::height() const
{
	return cairo_image_surface_get_height( _surface );
}

ARGBImageContainer::~ARGBImageContainer()
{
	cairo_destroy( _context );
	cairo_surface_destroy( _surface );
}


uint8_t* const 
ARGBImageContainer::getDataPointer(portIndex_t index) const
{
	return cairo_image_surface_get_data( _surface ) + index;   
}



Point<uint32_t, 3> 
ARGBImageContainer::increments(portIndex_t index) const
{
	uint32_t c1 = cairo_image_surface_get_stride( _surface );
	c1 /= sizeof(uint8_t);
	uint32_t c2 = c1 * width();
	uint32_t c3 = c2 * height();
	return Point<uint32_t, 3>(c1,c2,c3);
}



Point<uint32_t, 2> 
ARGBImageContainer::spanSize() const 
{
	return Point<uint32_t, 2>( width(), height() );
}


} //namespace
} //namespace
} //namespace

