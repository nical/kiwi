

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
{
	ScopedBlockMacro("cairo::RGBAImageContainer::constructor")
	//allocate the cairo surface	
	_surface = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32
		, size(0), size(1) );

	// create the cairo context
	_context = cairo_create( _surface );

	_dataPtr = reinterpret_cast<RGBA32Fragment*>(
		cairo_image_surface_get_data( _surface) );

	Debug::print() << "size = " << size.toStr()<<endl();

	initSubContainers();
}

RGBAImageContainer::RGBAImageContainer(
	RGBA32Fragment* data
	, const generic::Point<uint32_t, 2>& size ) 
{
	ScopedBlockMacro("cairo::RGBAImageContainer::constructor") 
	uint32_t stride = cairo_format_stride_for_width(
		CAIRO_FORMAT_ARGB32
		, size(0) );
	Debug::error() << "cairo_format_stride = " << stride << endl();
	_surface = cairo_image_surface_create_for_data(
		(kiwi::uint8_t*)data
		, CAIRO_FORMAT_ARGB32
		, size(0), size(1)
		, stride );

	_context = cairo_create( _surface );

	_dataPtr = (RGBA32Fragment*)data;

	initSubContainers();
}

RGBAImageContainer::RGBAImageContainer(const kiwi::string& file){
	loadPng(file);
	_dataPtr = reinterpret_cast<RGBA32Fragment*>(
		cairo_image_surface_get_data(_surface) );
	initSubContainers();
}

void RGBAImageContainer::initSubContainers()
{
	assert( _dataPtr == getDataPointer() );
	Debug::error() << spanSize().toStr() << endl();
	_subContainers.push_back(
		new ColorChannel(
			reinterpret_cast<kiwi::uint8_t*>(_dataPtr)+2
			, spanSize()
			, StrideVector( 4, 4*width() )
		) );
	_subContainers.push_back(
		new ColorChannel(
			reinterpret_cast<kiwi::uint8_t*>(_dataPtr)+1
			, spanSize()
			, StrideVector( 4, 4*width() )
		) );
	_subContainers.push_back(
		new ColorChannel(
			reinterpret_cast<kiwi::uint8_t*>(_dataPtr)
			, spanSize()
			, StrideVector( 4, 4*width() )
		) );
	_subContainers.push_back(
		new ColorChannel(
			reinterpret_cast<kiwi::uint8_t*>(_dataPtr)+3
			, spanSize()
			, StrideVector( 4, 4*width() )
		) );

	_sizeContainer.init( spanSize() );
}

kiwi::core::Container* RGBAImageContainer::subContainer(kiwi::uint32_t index){
	if(index == 4) return &_sizeContainer;
	if(index < nbSubContainers() ) return _subContainers[index];
	else return 0;
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

RGBAImageContainer::CoordinateVector RGBAImageContainer::spanSize() const
{
	return CoordinateVector( width(),height() );
}

RGBAImageContainer::StrideVector RGBAImageContainer::stride() const
{
	return StrideVector( 1, width() );
}
	

RGBA32Fragment* const RGBAImageContainer::getDataPointer() const
{
		cairo_image_surface_get_data ( _surface );
}


RGBA32Fragment RGBAImageContainer::getValue( kiwi::uint32_t pos ) const
{
	return *(_dataPtr + pos);
}

void RGBAImageContainer::setValue( kiwi::uint32_t pos, RGBA32Fragment value )
{
	*(getDataPointer() + pos) = value;
}

RGBA32Fragment RGBAImageContainer::getValue( const CoordinateVector& pos ) const
{
	return *(_dataPtr + pos(0) + pos(1) * width() );
}

void RGBAImageContainer::setValue( const CoordinateVector& pos, RGBA32Fragment value )
{
	*(getDataPointer() + pos(0) + pos(1) * width() ) = value;
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





} //namespace
} //namespace
} //namespace

