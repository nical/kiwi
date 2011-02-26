
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
		addReaderPort();
		addReaderPort();

		portIndex_t w_in = addWriterPort();
		portIndex_t r_out = addDataPort();
		associateWriterToDataPort(writerPort(w_in), dataPort(r_out));
		
	}

	void process(){
		ScopedBlockMacro(scop, "DummyFilter::Process")
		
		NumberContainer* ca
			= readerPort(0).getContainer<NumberContainer>();

		NumberContainer* cb
			= readerPort(1).getContainer<NumberContainer>();
		
		NumberContainer* result
			= writerPort(0).getContainer<NumberContainer>();

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
	ScopedBlockMacro(scop, "Filter::Test")
	DummyFilter filter;

	Debug::foo();
	
	assert( !filter.dataPort(0).isEnabled() );
	assert( filter.readerPort(0).isEnabled() );
	assert( filter.readerPort(1).isEnabled() );

	NumberContainer A(5);
	NumberContainer B(6);
	NumberContainer R(0);

	kiwi::core::Node nA( &A );
	kiwi::core::Node nB( &B );
	kiwi::core::Node nR( &R );

	assert( nA.dataPort(0).getContainer<kiwi::core::Container>() );
	assert( nB.dataPort(0).getContainer<kiwi::core::Container>() );
	assert( nR.dataPort(0).getContainer<kiwi::core::Container>() );
/*
	// check that association are made correctly
	assert( nA.dataPort(0).associatedReaderOutputPort()
		== &nA.dataPort(0) );
	assert( nB.dataPort(0).associatedReaderOutputPort()
		== &nB.dataPort(0) );
	assert( nR.dataPort(0).associatedReaderOutputPort()
		== &nR.dataPort(0) );
*/
	assert( !filter.readerPort(0).isConnected() );
	assert( !filter.readerPort(1).isConnected() );
	assert( !filter.writerPort(0).isConnected() );

	assert( nA.dataPort(0) >> filter.readerPort(0) );	
	assert( nB.dataPort(0) >> filter.readerPort(1) );
	assert( nR.dataPort(0) >> filter.writerPort(0) );

	assert( filter.readerPort(0).isConnected() );
	assert( filter.readerPort(1).isConnected() );
	assert( filter.writerPort(0).isConnected() );
	assert( nA.dataPort(0).isConnectedToReader() );
	assert( nB.dataPort(0).isConnectedToReader() );
	assert( nR.dataPort(0).isConnectedToWriter() );

	assert( nR.dataPort(0).getContainer<NumberContainer>()->getValue() == 0 );

	assert( filter.readerPort(0).connectedPort()->node() );

	assert( nR.dataPort(0).node() );
	assert( nR.dataPort(0).WriterConnector::connectedInstance() == &filter.writerPort(0) ); 
	assert( &nR.dataPort(0) == filter.writerPort(0).PortConnector::connectedInstance() ); //fail
	assert( filter.writerPort(0).connectedPort() );
	assert( filter.writerPort(0).connectedPort()->node() ); // fail
	assert( filter.writerPort(0).connectedPort()->node() == &nR );

	filter.process();

	Debug::print() << R.getValue() << endl();
	assert( R.getValue() == 11 );

	NumberContainer* pr = filter.dataPort(0).getContainer<NumberContainer>();
	assert( pr );
	assert( pr->getValue() == 11 );

	return 0;
}

