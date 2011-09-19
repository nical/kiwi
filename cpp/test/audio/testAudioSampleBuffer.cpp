

#include "core/Commons.hpp"

#include "audio/AudioSampleBuffer.hpp"



int main()
{

SCOPEDBLOCK_MACRO(s2, "kiwi::testAudioSampleBuffer");

kiwi::debug.beginBlock("int main() ");

	kiwi::debug.beginBlock("Allocate the resources");
		kiwi::audio::AudioSampleBuffer<float>(new float[1024], 1024, true);


	kiwi::debug.endBlock();
	
	
	
kiwi::debug.endBlock();
	return 0;
}

