
#pragma once
#ifndef KIWI_IMAGE_COPYIMAGEFILTER_HPP
#define KIWI_IMAGE_COPYIMAGEFILTER_HPP

#include "kiwi/core/Filter.hpp"
#include "kiwi/image/cairo/ImageContainer.hpp"
#include "kiwi/generic/PointAccessContainerInterface.hpp"
#include "kiwi/generic/ArrayContainer.hpp"

namespace kiwi{
namespace image{


/**
 * @brief Duplicates the input images.
 *
 * Note that it is possible to compose an image with any color channel in input,
 * which may be usefull to create an image container from independent color channel
 * containers.
 */ 
class CopyImageFilter : public kiwi::core::Filter
{
public:
	enum{ R = 0, G = 1, B = 2, A = 3 };

	CopyImageFilter(){
		addReaderPort(); // R
		addReaderPort(); // G
		addReaderPort(); // B
		addReaderPort(); // A

		// RGBA result of the copy
		kiwi::portIndex_t w_in = addWriterPort(); 
		kiwi::portIndex_t r_out = addDataPort();
		//associateWriterToReader( writerPort(w_in) , dataPort(r_out) );
	}

	void process(){
		ScopedBlockMacro(scop,"CopyImageFilter::process")
		typedef kiwi::generic::PointAccessContainerInterface<kiwi::uint8_t,2> ColorBuffer;
		//typedef kiwi::generic::ArrayContainer<kiwi::uint8_t,2> ColorBuffer;
		typedef kiwi::generic::Point<kiwi::uint32_t, 2> CoordinateVector;

		ColorBuffer* r
			= readerPort(R).connectedPort()
				->safeDownCastContainer<ColorBuffer>();
		ColorBuffer* g
			= readerPort(G).connectedPort()
				->safeDownCastContainer<ColorBuffer>();
		ColorBuffer* b
			= readerPort(B).connectedPort()
				->safeDownCastContainer<ColorBuffer>();
		ColorBuffer* a
			= readerPort(A).connectedPort()
				->safeDownCastContainer<ColorBuffer>();

		Debug::plop();
		
		assert( writerPort(0).connectedPort() );
		kiwi::image::cairo::RGBAImageContainer* result
			= writerPort(0).connectedPort()
				->safeDownCastContainer<kiwi::image::cairo::RGBAImageContainer>();

		if(!a) Debug::print() << "alpha channel not found\n";
		if(!r) Debug::print() << "red channel not found\n";
		if(!g) Debug::print() << "green channel not found\n";
		if(!b) Debug::print() << "blue channel not found\n";

		Debug::plop();

		if(!result){
			Debug::print() << "Allocate result container\n";
			CoordinateVector size;
			if(a) {
				size = a->spanSize();
			}else if(r){
				size = r->spanSize();
			}else if(g){
				size = g->spanSize();
			}else if(b){
				size = b->spanSize();
			}else { return; }

			result = new kiwi::image::cairo::RGBAImageContainer(size);
			setDataPortContainer(dataPort(0), result );
		}
		//cairo_surface_flush( result->getSurface() ); // TODO

		Debug::plop();

		for(kiwi::uint32_t x = 0; x < result->width(); ++x)
			for(kiwi::uint32_t y = 0; y < result->height(); ++y){
				kiwi::uint8_t va = a? a->getValue(CoordinateVector(x,y)) : 255; 
				kiwi::uint8_t vr = r? r->getValue(CoordinateVector(x,y)) : 0; 
				kiwi::uint8_t vg = g? g->getValue(CoordinateVector(x,y)) : 0; 
				kiwi::uint8_t vb = b? b->getValue(CoordinateVector(x,y)) : 0; 
				RGBA32Fragment f(vr,vg,vb,va);
				result->setValue(CoordinateVector(x,y), f);
			}
		//cairo_surface_mark_dirty(result->getSurface() ); // TODO
	}

	kiwi::utils::Tags readerInputTags(kiwi::portIndex_t index) const{
		return kiwi::utils::Tags("#any");
	}

};


}//namespace
}//namespace

#endif
