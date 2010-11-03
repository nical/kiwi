#pragma once

#include <cairo.h>
#include "generic/Point.hp"
#ifndef KIWI_CAIROIMAGECONTAINER_HPP
#define KIWI_CAIROIMAGECONTAINER_HPP


namespace kiwi
{
namespace image
{

using namespace kiwi::generic;

class CairoImageContainer<int imageFormat> : public Resource
{
public:
	CairoImageContainer(const Point<unsigned int, 2>& size) : Resource()
	{
		_surface =  cairo_image_surface_create(
			imageFormat
			, size(0), size(1) );
		_context = cairo_create( _surface );
	}
	
	inline cairo_t getContext() { return _context; }

	void saveToPng(string path)
	{
		cairo_surface_write_to_png( _surface, path.c_str() );
	}

/*
 * width = cairo_image_surface_get_width (surface);
    height = cairo_image_surface_get_height (surface);
*/
	~CairoImageContainer()
	{
		cairo_destroy( _contex );
        cairo_surface_destroy( _surface );
	}
protected:
cairo_surface_t *_surface;
cairo_t* _context;

};

typedef CairoImageContainer<CAIRO_FORMAT_ARGB32> CairoImageContainerRVBA;

} //namsepace
} //namsepace

#endif
