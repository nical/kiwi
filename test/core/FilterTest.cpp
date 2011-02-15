
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
		ScopedBlockMacro(scop, "DummyFilter::Process")
		
		NumberContainer* ca
			= readerInputPort(0).connectedOutput()
				->getContainer<NumberContainer>();

		NumberContainer* cb
			= readerInputPort(1).connectedOutput()
				->getContainer<NumberContainer>();
		
		NumberContainer* result
			= writerInputPort(0).connectedOutput()
				->getContainer<NumberContainer>();

		assert(ca);
		assert(cb);
		assert(result);

		int A = ca->getValue();
		int B = cb->getValue();
		result->setValue( A + B );
		assert( result->getValue() == 11 );
	}
};



int main()
{

	DummyFilter filter;

	assert( !filter.readerOutputPort(0).isEnabled() );
	assert( filter.readerInputPort(0).isEnabled() );
	assert( filter.readerInputPort(1).isEnabled() );

	NumberContainer A(5);
	NumberContainer B(6);
	
	NumberContainer R(0);

	kiwi::core::Node nA( &A );
	kiwi::core::Node nB( &B );
	kiwi::core::Node nR( &R );

	// check that association are made correctly
	assert( nA.writerOutputPort(0).associatedReaderOutputPort()
		== &nA.readerOutputPort(0) );
	assert( nB.writerOutputPort(0).associatedReaderOutputPort()
		== &nB.readerOutputPort(0) );
	assert( nR.writerOutputPort(0).associatedReaderOutputPort()
		== &nR.readerOutputPort(0) );

	nA.readerOutputPort(0) >> filter.readerInputPort(0);	
	nB.readerOutputPort(0) >> filter.readerInputPort(1);
	nR.writerOutputPort(0) >> filter.writerInputPort(0);

	assert( filter.readerInputPort(0).isConnected() );
	assert( filter.readerInputPort(1).isConnected() );
	assert( filter.writerInputPort(0).isConnected() );

	filter.process();

	Debug::print() << R.getValue() << endl();
	assert( R.getValue() == 11 );

	NumberContainer* pr = filter.readerOutputPort(0).getContainer<NumberContainer>();
	assert( pr );
	assert( pr->getValue() == 11 );

	return 0;
}

