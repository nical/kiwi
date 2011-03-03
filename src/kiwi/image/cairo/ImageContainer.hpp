
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
#include "kiwi/generic/ArrayContainer.hpp"
#include "kiwi/generic/Point.hpp"
#include "kiwi/generic/PointVectorContainer.hpp"
#include "kiwi/core/Tags.hpp"
#include "kiwi/image/RGBA32Fragment.hpp"


namespace kiwi{
namespace image{
namespace cairo{




/**
 * @brief 8bits per channel ARGB Image container using the cairo graphic library
 * as backend.
 *
 */
class RGBAImageContainer : public generic::ArrayContainerInterface<RGBA32Fragment, 2>
{
public:

	typedef RGBA32Fragment ValueType;
	static const kiwi::uint32_t Dimension = 2;
	typedef generic::ArrayContainerInterface<uint8_t, 2> MotherClass;
	typedef generic::ArrayContainer<uint8_t, 2> ColorChannel;
	typedef MotherClass::CoordinateVector CoordinateVector;
	typedef MotherClass::StrideVector StrideVector;
	enum{ R = 0, V = 1, B = 2, A = 3 };
	
	// ----------------------------------------- Constructors/destructor
	/**
	 * @brief Constructor (allocates the data).
	 */
	RGBAImageContainer(const CoordinateVector& size);
	
	/**
	 * @brief Constructor (allocates the data).
	 */
	RGBAImageContainer(const kiwi::string& file);

	/**
	 * @brief Constructor (use pre-allocated data).
	 */
	RGBAImageContainer(RGBA32Fragment* data, const CoordinateVector& size);

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
	cairo_t* getContext();
	/**
	 * @brief Returns this image's cairo surface.
	 *
	 * This is specific to cairo's functionning.
	 */
	cairo_surface_t* getSurface();

	/**
	 * @brief Saves the surface into a .png file.
	 */
	void saveToPng(const kiwi::string& path);

	void loadPng(const kiwi::string& path);

	/**
	 * @brief Returns the image's width.
	 */
	kiwi::uint32_t width() const;

	/**
	 * @brief Returns the image's height.
	 */
	kiwi::uint32_t height() const;




	// ----------------------------------- virtual method implementation
	
	Tags tags() const { return Tags("#RGBA"); }


	virtual kiwi::uint32_t memoryEstimation() const
	{
		return size()*sizeof(kiwi::uint8_t)*4;
	}

	virtual bool isComposite() const { return true; }

	virtual kiwi::uint32_t nbSubContainers() const { return 4; }

	virtual kiwi::core::Container* subContainer(kiwi::uint32_t index);

	virtual kiwi::uint32_t size() const { return width() * height(); }
	
	virtual CoordinateVector spanSize() const;


	//data access
	virtual RGBA32Fragment* const getDataPointer() const;

	virtual StrideVector stride() const;
	
	virtual RGBA32Fragment getValue( kiwi::uint32_t pos ) const ;
	virtual void setValue( kiwi::uint32_t pos, RGBA32Fragment value ) ;

	virtual RGBA32Fragment getValue( const CoordinateVector& pos ) const;
	virtual void setValue( const CoordinateVector& pos, RGBA32Fragment value );

	
	//factory
	static void registerToFactory(kiwi::utils::NodeFactory& factory, const kiwi::string& filterId);


protected:
	cairo_surface_t *_surface;
	cairo_t* _context;
	RGBA32Fragment* _dataPtr;
	std::vector<ColorChannel*> _subContainers;
	kiwi::generic::PointVectorContainer<kiwi::uint32_t,2> _sizeContainer;

	void initSubContainers();
};





} //namsepace
} //namsepace
} //namsepace


#endif
