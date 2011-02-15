
#pragma once
#ifndef KIWI_IMAGE_COPYIMAGEFILTER_HPP
#define KIWI_IMAGE_COPYIMAGEFILTER_HPP



namespace kiwi{
namespace image{



class CopyImageFilter
{
public:
	CopyImageFilter(){
		_result = new kiwi::generic::NumberContainer<KIWI_ADDFILTER_TYPE>();
		addReaderInputPort(); // R
		addReaderInputPort(); // G
		addReaderInputPort(); // B
		addReaderInputPort(); // A

		WriterInputPort* w_in = addWriterInputPort(); // RGBA result of the copy
		
		ReaderOutputPort* r_out = addReaderOutputPort();
		associateWriterToReader( *w_in , *r_out );
	}

protected:
	
};


}//namespace
}//namespace
