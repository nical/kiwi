
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
#include "kiwi/generic/StructuredArrayContainer.hpp"
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
class RGBAImageContainer : public generic::StructuredArrayContainer<uint8_t, 2>
{
public:

	typedef uint32_t ValueType;
	static const kiwi::uint32_t Dimension = 2;
	typedef generic::StructuredArrayContainer<uint8_t, 2> MotherClass;
	typedef MotherClass::CoordinateVector CoordinateVector;
	typedef MotherClass::StrideVector StrideVector;

	
	// ----------------------------------------- Constructors/destructor
	/**
	 * @brief Constructor (allocates the data).
	 */
	RGBAImageContainer(const CoordinateVector& size);
	
	/**
	 * @brief Constructor (allocates the data).
	 */
	RGBAImageContainer(const kiwi::string& file){
		loadPng(file);
		_data = cairo_image_surface_get_data (_surface);
		
		MotherClass::init( _data
			, CoordinateVector(width(), height())
			,"[R%G%B%A]");
	}

	/**
	 * @brief Constructor (use pre-allocated data).
	 */
	RGBAImageContainer(kiwi::uint8_t* data, const CoordinateVector& size);

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
	void saveToPng(const kiwi::string& path);

	void loadPng(const kiwi::string& path);

	/**
	 * @brief Returns the image's width.
	 */
	kiwi::uint32_t width() const; // { return _spanSize(0); }

	/**
	 * @brief Returns the image's height.
	 */
	kiwi::uint32_t height() const; // { return _spanSize(1); }




	// ----------------------------------- virtual method implementation
	
	Tags tags() const { return Tags("#RGBA"); }


	virtual kiwi::uint32_t memoryEstimation() const
	{
		return size()*sizeof(kiwi::uint8_t)*4;
	}


	static void registerToFactory(kiwi::core::NodeFactory& factory, const kiwi::string& filterId);


protected:
	cairo_surface_t *_surface;
	cairo_t* _context;

};





} //namsepace
} //namsepace
} //namsepace


#endif
