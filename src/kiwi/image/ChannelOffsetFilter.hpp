
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
		addReaderInputPort(); // Channel
		addReaderInputPort(); // displacement vector
		//addReaderInputPort(); // region

		// Result (channel)
		kiwi::portIndex_t w_in = addWriterInputPort(); 
		kiwi::portIndex_t r_out = addReaderOutputPort();
		associateWriterToReader( writerInputPort(w_in) , readerOutputPort(r_out) );
	}

	void process(){
		ScopedBlockMacro(scop,"ChannelOffsetFilter::process")
		typedef kiwi::generic::PointAccessContainerInterface<kiwi::uint8_t,2> ColorBuffer;
		typedef kiwi::generic::PointVectorContainer<kiwi::uint32_t, 2> PointVectorContainer;
		typedef kiwi::generic::Point<kiwi::uint32_t, 2> CoordinateVector;
		typedef kiwi::generic::RectangleContainer<2> RegionContainer;


		ColorBuffer* chan
			= readerInputPort(0).connectedOutput()
				->getContainer<ColorBuffer>();
				
		PointVectorContainer* vect
			= readerInputPort(1).connectedOutput()
				->getContainer<PointVectorContainer>();
/*
		RegionContainer* regionInput
			= readerInputPort(2).connectedOutput()
				->getContainer<RegionContainer>();
*/
		ColorBuffer* result
			= writerInputPort(0).connectedOutput()
				->getContainer<ColorBuffer>();
				
		if(!chan) Debug::print() << "input channel not found\n";
		if(!vect) Debug::print() << "input offset vector not found\n";
//		if(!regionInput) Debug::print() << "input region not found\n";
		if(!result) Debug::print() << "output channel not found\n";

		if(!result){
			Debug::print() << "Allocate result container\n";
			CoordinateVector size;
			if(chan) {
				result = new kiwi::generic::ArrayContainer<kiwi::uint8_t,2>(chan->spanSize());
				setPortContainer(readerOutputPort(0), result );
			}else { return; }
		}
/*
		CoordinateVector topLeft;

		if(!regionInput){
			topLeft = 
		}
*/		
		CoordinateVector pos;
		for(pos(0) = 0; pos(0) < result->spanSize()[0]; ++pos(0))
			for(pos(1) = 0; pos(1) < result->spanSize()[1]; ++pos(1)){
				kiwi::uint32_t val = chan->getValue(pos);
				CoordinateVector newpos = (pos+*vect) % result->spanSize();
				result->setValue(newpos, val);
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

