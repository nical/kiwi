

#include "ImageContainer.hpp"

namespace kiwi{
namespace image{
namespace cairo{	

/*
kiwi::core::Node* newCairoImageNode(){
	return new kiwi::core::Node( new RGBAImageContainer( generic::Point<uint32_t, 2>() ));
}
*/

RGBAImageContainer::RGBAImageContainer(const generic::Point<uint32_t, 2>& size) 
	: generic::StructuredArrayContainer<uint8_t, 2>()
{
	//allocate the cairo surface	
	_surface = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32
		, size(0), size(1) );

	// create the cairo context
	_context = cairo_create( _surface );

	//get the data pointer
	_data = cairo_image_surface_get_data (_surface);
	
	//init the mother class stuff (includes creating subcontainers)
	MotherClass::init(_data ,size,"[R%G%B%A]");
}

RGBAImageContainer::RGBAImageContainer(
	uint8_t* data
	, const generic::Point<uint32_t, 2>& size ) 
		: MotherClass()
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

	MotherClass::init(data ,size,"[R%G%B%A]");
}


cairo_t* 
RGBAImageContainer::getContext() 
{ 
	return _context; 
}


cairo_surface_t* 
RGBAImageContainer::getSurface() 
{ 
	return _surface; 
}


void 
RGBAImageContainer::saveToPng(const kiwi::string& path)
{
	cairo_surface_write_to_png( _surface, path.c_str() );
}

void
RGBAImageContainer::loadPng(const kiwi::string& path)
{
	_surface = cairo_image_surface_create_from_png(path.c_str() );
}


uint32_t 
RGBAImageContainer::width() const
{
	return cairo_image_surface_get_width( _surface );
}

uint32_t 
RGBAImageContainer::height() const
{
	return cairo_image_surface_get_height( _surface );
}

/*
void RGBAImageContainer::registerToFactory(kiwi::core::NodeFactory& factory, const kiwi::string& filterId)
{
	kiwi::string tags("#Container#cairo");
	kiwi::string name("CairoImageContainer");

	factory.registerNode( filterId
			, kiwi::core::Descriptor<kiwi::core::Node>(
				name
				, newCairoImageContainer
				, tags )
		);
}
*/
RGBAImageContainer::~RGBAImageContainer()
{
	// TODO: generates an error within reference counting cairo internals
	// see cairo_surface_make_dirty or something like this, it might help...
	/*
	cairo_destroy( _context );
	cairo_surface_destroy( _surface );
	*/ 
}

/*
uint8_t* const 
RGBAImageContainer::getDataPointer(portIndex_t index) const
{
	return cairo_image_surface_get_data( _surface ) + index;   
}
*/




} //namespace
} //namespace
} //namespace

