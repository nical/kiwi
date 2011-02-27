
#pragma once
#ifndef KIWI_IMAGE_CHANNELOFFSETFILTER_HPP
#define KIWI_IMAGE_CHANNELOFFSETFILTER_HPP

#include "kiwi/core/Filter.hpp"
#include "kiwi/generic/PointAccessContainerInterface.hpp"
#include "kiwi/generic/PointVectorContainer.hpp"
#include "kiwi/generic/RectangleContainer.hpp"
#include "kiwi/generic/ArrayContainer.hpp"

namespace kiwi{
namespace image{



class ChannelOffsetFilter : public kiwi::core::Filter
{
public:

	ChannelOffsetFilter(){
		addReaderPort(); // Channel
		addReaderPort(); // displacement vector
		addReaderPort(); // region
		addReaderPort(); // mask

		// Result (channel)
		kiwi::portIndex_t w_in = addWriterPort(); 
		kiwi::portIndex_t r_out = addDataPort();
		//associateWriterToReader( writerPort(w_in) , dataPort(r_out) );
	}

	void process(){
		ScopedBlockMacro(scop,"ChannelOffsetFilter::process")
		typedef kiwi::generic::PointAccessContainerInterface<kiwi::uint8_t,2> ColorBuffer;
		typedef kiwi::generic::PointVectorContainer<kiwi::uint32_t, 2> PointVectorContainer;
		typedef kiwi::generic::Point<kiwi::uint32_t, 2> CoordinateVector;
		typedef kiwi::generic::RectangleContainer<kiwi::int32_t, 2> RegionContainer;


		ColorBuffer* chan = readerPort(0).getContainer<ColorBuffer>();
				
		PointVectorContainer* vect
			= readerPort(1).getContainer<PointVectorContainer>();

		RegionContainer* regionInput
			= readerPort(2).getContainer<RegionContainer>();

		ColorBuffer* mask = readerPort(3).getContainer<ColorBuffer>();	

		ColorBuffer* result	= writerPort(0).getContainer<ColorBuffer>();
				
		if(!chan) Debug::print() << "input channel not found\n";
		if(!vect) Debug::print() << "input offset vector not found\n";
		if(!regionInput) Debug::print() << "input region not found\n";
		if(!result) Debug::print() << "output channel not found\n";
		if(!mask) Debug::print() << "input mask not found\n";

		Debug::plop();

		if(!result){
			Debug::print() << "Allocate result container\n";
			CoordinateVector size;
			if(chan) {
				result = new kiwi::generic::ArrayContainer<kiwi::uint8_t,2>(chan->spanSize());
				setDataPortContainer(dataPort(0), result );
			}else { return; }
		}
		
		Debug::plop();
		
		generic::Rect<kiwi::int32_t,2> region;
		if(regionInput){
			region = regionInput->rect();
		}else{
			region.position(0) = 0;
			region.position(1) = 0;
			region.size(0) =  result->spanSize()[0];
			region.size(1) =  result->spanSize()[1];
		}

		Debug::plop();
		
		CoordinateVector pos;
		for(pos(0) = region.position(0); pos(0) < region.size(0); ++pos(0))
			for(pos(1) = region.position(1); pos(1) < region.size(1); ++pos(1)){
				float maskValue = 1;
				if(mask) maskValue = (float)mask->getValue(pos)/255.0;
				//if(maskValue < 0.5) Debug::bar();
				CoordinateVector newpos = (pos+(*vect * maskValue)) % result->spanSize();
				kiwi::uint32_t val = chan->getValue(newpos);
				//Debug::print() << (newpos - pos)
				result->setValue(pos, val);
			}
	}

	kiwi::Tags readerInputTags(kiwi::portIndex_t index) const{
		return kiwi::Tags("#any");// TODO
	}

protected:
	
};


}//namespace
}//namespace

#endif

