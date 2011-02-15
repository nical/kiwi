
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Filter.hpp"
#include "kiwi/generic/NumberContainer.hpp"

#include <assert.h>

using namespace kiwi;
using namespace kiwi::core;

typedef kiwi::generic::NumberContainer<int> NumberContainer;

class DummyFilter : public kiwi::core::Filter
{
public:
	DummyFilter(){
		addReaderInputPort();
		addReaderInputPort();

		portIndex_t w_in = addWriterInputPort();
		portIndex_t r_out = addReaderOutputPort();
		associateWriterToReader(writerInputPort(w_in), readerOutputPort(r_out));
		
	}

	void process(){
		ScopedBlockMacro(__scop, "DummyFilter::Process")
	}

	virtual kiwi::Tags readerInputTags( portIndex_t index ) const{
		return kiwi::Tags("#any");
	}
};



int main()
{

	DummyFilter filter;

	assert( !filter.readerOutputPort(0).isEnabled() );

	NumberContainer A(5);
	NumberContainer B(6);
	
	NumberContainer R(0);

	kiwi::core::Node nA( &A );
	kiwi::core::Node nB( &B );

	filter.process(); // same as process()

	return 0;
}

