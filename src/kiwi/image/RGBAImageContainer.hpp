#pragma once

#ifndef KIWI_IMAGE_RGBAIMAGECONTAINER_HPP
#define KIWI_IMAGE_RGBAIMAGECONTAINER_HPP

#include "kiwi/image/RGBA32Fragment.hpp"
#include "kiwi/generic/ArrayContainer.hpp"
#include "kiwi/generic/ArrayContainerInterface.hpp"


namespace kiwi{
namespace image{

template<typename Pixel = RGBA32Fragment>
class RGBAImageContainer : public generic::ArrayContainerInterface<Pixel, 2>
{
public:
	typedef Pixel Fragment;
	typedef typename Pixel::ColorElement ColorElement;
	static const kiwi::uint32_t Dimension = 2;
	typedef generic::ArrayContainerInterface<ColorElement, 2> MotherClass;
	typedef generic::ArrayContainer<ColorElement, 2> ColorChannel;
	typedef typename MotherClass::CoordinateVector CoordinateVector;
	typedef typename MotherClass::StrideVector StrideVector;

	RGBAImageContainer(kiwi::uint32_t width, kiwi::uint32_t height){
		_data = new Pixel[width*height];
		_ownData = true;
		_width = width;
		_height = height;
		CoordinateVector sizeVect =  CoordinateVector(width,height);
		StrideVector strideVect =  StrideVector(4, width*4);
		_subContainers[0] = new ColorChannel(
			(ColorElement*)_data
			, sizeVect
			, strideVect);	
		_subContainers[1] = new ColorChannel(
			((ColorElement*)_data)+1
			, sizeVect
			, strideVect);	
		_subContainers[2] = new ColorChannel(
			((ColorElement*)_data)+2
			, sizeVect
			, strideVect);	
		_subContainers[3] = new ColorChannel(
			((ColorElement*)_data)+3
			, sizeVect
			, strideVect);	
	}

	~RGBAImageContainer(){
		if(_ownData) delete[] _data;
	}

	/**
	 * @brief Returns the image's width.
	 */
	kiwi::uint32_t width() const  { return _width; }

	/**
	 * @brief Returns the image's height.
	 */
	kiwi::uint32_t height() const { return _height; }

	/**
	 * @brief Returns true because this is a composite container.
	 */ 
	virtual bool isComposite() const {return true;}

	/**
	 * @brief Returns the number of sub-arrays.
	 */ 
	virtual kiwi::uint32_t nbSubContainers() const { return 4; }

	/**
	 * @brief Returns the ArrayContainers that are part of this structured container.
	 */ 
	virtual core::Container* subContainer(kiwi::uint32_t index){
		if(index < 4 ){
			return _subContainers[index];
		}else{ return 0; }
	}

	kiwi::uint32_t layout() const {return 0x7;}


	// ----------------------------------- virtual method implementation
	
	Tags tags() const { return Tags("#RGBA"); }

	virtual kiwi::uint32_t size() const {return _width*_height;}

	virtual kiwi::uint32_t memoryEstimation() const{
		return size()*sizeof(Pixel);
	}

	virtual Pixel getValue( kiwi::uint32_t pos ) const{
		return _data[pos];
	}

	virtual void setValue( kiwi::uint32_t pos, Pixel value ){
		_data[pos] = value;
	}
	
	virtual Pixel getValue( const CoordinateVector& pos ) const{
		return _data[pos(0)+_width*pos(1)];
	}

	virtual void setValue( const CoordinateVector& pos, Pixel value ){
		_data[pos(0)+_width*pos(1)] = value;
	}

	virtual Pixel* const getDataPointer() const {
		return _data;
	}

	virtual CoordinateVector spanSize() const {
		return CoordinateVector(_width, _height);
	}

	/**
	 * Returns the stride.
	 */
	virtual StrideVector stride() const {return StrideVector(1,_width);}	
	/**
	 * Returns the stride of a given dimension.
	 */
	virtual kiwi::uint32_t stride(kiwi::uint32_t dimension) const {
		if( dimension == 0){
			return 1;
		}else if( dimension == 1){
			return _width;
		}
	};

	virtual bool hasPremultipliedAlpha() const {
		return false;
	}

protected:
	Pixel* _data;
	kiwi::uint32_t _width;
	kiwi::uint32_t _height;
	bool _ownData;
	ColorChannel* _subContainers[4];
};


}//namespace
}//namespace


#endif
