
#pragma once
#ifndef KIWI_IMAGE_COPYIMAGEFILTER_HPP
#define KIWI_IMAGE_COPYIMAGEFILTER_HPP

#include "kiwi/core/Filter.hpp"
#include "kiwi/image/cairo/ImageContainer.hpp"
#include "kiwi/generic/PointAccessContainerInterface.hpp"
#include "kiwi/generic/ArrayContainer.hpp"

namespace kiwi{
namespace image{



class CopyImageFilter : public kiwi::core::Filter
{
public:
	enum{ R = 0, G = 1, B = 2, A = 3 };

	CopyImageFilter(){
		addReaderInputPort(); // R
		addReaderInputPort(); // G
		addReaderInputPort(); // B
		addReaderInputPort(); // A

		// RGBA result of the copy
		kiwi::portIndex_t w_in = addWriterInputPort(); 
		kiwi::portIndex_t r_out = addReaderOutputPort();
		associateWriterToReader( writerInputPort(w_in) , readerOutputPort(r_out) );
	}

	void process(){
		ScopedBlockMacro(scop,"CopyImageFilter::process")
		typedef kiwi::generic::PointAccessContainerInterface<kiwi::uint8_t,2> ColorBuffer;
		//typedef kiwi::generic::ArrayContainer<kiwi::uint8_t,2> ColorBuffer;
		typedef kiwi::generic::Point<kiwi::uint32_t, 2> CoordinateVector;

		ColorBuffer* r
			= readerInputPort(R).connectedOutput()
				->getContainer<ColorBuffer>();
		ColorBuffer* g
			= readerInputPort(G).connectedOutput()
				->getContainer<ColorBuffer>();
		ColorBuffer* b
			= readerInputPort(B).connectedOutput()
				->getContainer<ColorBuffer>();
		ColorBuffer* a
			= readerInputPort(A).connectedOutput()
				->getContainer<ColorBuffer>();

		Debug::plop();
		
		assert( writerInputPort(0).connectedOutput() );
		kiwi::image::cairo::RGBAImageContainer* result
			= writerInputPort(0).connectedOutput()
				->getContainer<kiwi::image::cairo::RGBAImageContainer>();

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
			setPortContainer(readerOutputPort(0), result );
		}
		cairo_surface_flush( result->getSurface() );

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
		cairo_surface_mark_dirty(result->getSurface() );
	}

	kiwi::Tags readerInputTags(kiwi::portIndex_t index) const{
		return kiwi::Tags("#any");
	}

};


}//namespace
}//namespace

#endif
