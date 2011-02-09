

#include "ImageContainer.hpp"

namespace kiwi{
namespace image{
namespace cairo{	

//using namespace generic;

RGBAImageContainer::RGBAImageContainer(const generic::Point<uint32_t, 2>& size) 
	: generic::ArrayContainerInterface<uint8_t, 2>()
{			
	_surface = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32
		, size(0), size(1) );
		
	_context = cairo_create( _surface );
}

RGBAImageContainer::RGBAImageContainer(
	uint8_t* data
	, const generic::Point<uint32_t, 2>& size ) 
		: generic::ArrayContainerInterface<uint8_t, 2>()
{	
	uint32_t stride = cairo_format_stride_for_width(
		CAIRO_FORMAT_ARGB32
		, size(0) );
		
	_surface = cairo_image_surface_create_for_data(
		data
		, CAIRO_FORMAT_ARGB32
		, size(0), size(1)
		, stride );
		
	_context = cairo_create( _surface );
}

inline 
cairo_t* 
RGBAImageContainer::getContext() 
{ 
	return _context; 
}

inline 
cairo_surface_t* 
RGBAImageContainer::getSurface() 
{ 
	return _surface; 
}


void 
RGBAImageContainer::saveToPng(string path)
{
	cairo_surface_write_to_png( _surface, path.c_str() );
}

inline 
uint32_t 
RGBAImageContainer::width() const
{
	return cairo_image_surface_get_width( _surface );
}

inline 
uint32_t 
RGBAImageContainer::height() const
{
	return cairo_image_surface_get_height( _surface );
}

RGBAImageContainer::~RGBAImageContainer()
{
	cairo_destroy( _context );
	cairo_surface_destroy( _surface );
}


uint8_t* const 
RGBAImageContainer::getDataPointer(portIndex_t index) const
{
	return cairo_image_surface_get_data( _surface ) + index;   
}



generic::Point<uint32_t, 3>
RGBAImageContainer::increments(portIndex_t index) const
{
	uint32_t c1 = 4;//cairo_image_surface_get_stride( _surface );
	c1 /= sizeof(uint8_t);
	uint32_t c2 = c1 * width();
	uint32_t c3 = c2 * height();
	return generic::Point<uint32_t, 3>(c1,c2,c3);
}



generic::Point<uint32_t, 2>
RGBAImageContainer::spanSize() const 
{
	return generic::Point<uint32_t, 2>( width(), height() );
}

Tags RGBAImageContainer::readerOutputTags(portIndex_t)
{
	return Tags("#rgba8#array2char");
}

Tags RGBAImageContainer::writerOutputTags(portIndex_t)
{
	return Tags("#rgba8#array2char");
}


} //namespace
} //namespace
} //namespace

