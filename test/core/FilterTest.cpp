
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Filter.hpp"
#include "kiwi/generic/NumberContainer.hpp"
#include "kiwi/core/StaticReaderPort.hpp"
#include "kiwi/core/StaticWriterPort.hpp"

#include <assert.h>

using namespace kiwi;
using namespace kiwi::core;

typedef kiwi::generic::NumberContainer<int> NumberContainer;

class DummyFilter : public kiwi::core::DynamicNode
{
public:
	DummyFilter(){
    _src1 =  new StaticReaderPort<NumberContainer>(this); 
    _src2 =  new StaticReaderPort<NumberContainer>(this);
    _dest1 =  new StaticWriterPort<NumberContainer>(this);
    
		addReaderPort( _src1 );
		addReaderPort( _src2 );

		addWriterPort( _dest1 );

    portIndex_t r_out = addDataPort();
		associateWriterToDataPort( *_dest1, dataPort(r_out));
	}

	void process(){
		ScopedBlockMacro( "DummyFilter::Process")
		
		NumberContainer* ca
			= _src1->getContainer();

		NumberContainer* cb
			= _src2->getContainer();
		
		NumberContainer* result
			= writerPort(0).safeDownCastContainer<NumberContainer>();

		assert(ca);
		assert(cb);
		assert(result);

		int A = ca->getValue();
		int B = cb->getValue();
		result->setValue( A + B );
		assert( result->getValue() == 11 );
	}

  protected:
    StaticReaderPort<NumberContainer>* _src1;
    StaticReaderPort<NumberContainer>* _src2;
    StaticWriterPort<NumberContainer>* _dest1;
};



int main()
{
	ScopedBlockMacro( "Filter::Test")
	DummyFilter filter;

	Debug::foo();
	
	//assert( !filter.dataPort(0).isEnabled() );
	assert( filter.readerPort(0).isEnabled() );
	assert( filter.readerPort(1).isEnabled() );

	NumberContainer A(5);
	NumberContainer B(6);
	NumberContainer R(0);

	kiwi::core::DynamicNode nA( &A );
	kiwi::core::DynamicNode nB( &B );
	kiwi::core::DynamicNode nR( &R );

	assert( nA.dataPort(0).safeDownCastContainer<kiwi::core::Container>() );
	assert( nB.dataPort(0).safeDownCastContainer<kiwi::core::Container>() );
	assert( nR.dataPort(0).safeDownCastContainer<kiwi::core::Container>() );
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

	assert( nR.dataPort(0).safeDownCastContainer<NumberContainer>()->getValue() == 0 );

	assert( filter.readerPort(0).connectedPort()->node() );

	assert( nR.dataPort(0).node() );
	assert( filter.writerPort(0).connectedPort() );
	assert( filter.writerPort(0).connectedPort()->node() ); // fail
	assert( filter.writerPort(0).connectedPort()->node() == &nR );

	filter.process();

	Debug::print() << R.getValue() << endl();
	assert( R.getValue() == 11 );

	NumberContainer* pr = filter.dataPort(0).safeDownCastContainer<NumberContainer>();
	assert( pr );
	assert( pr->getValue() == 11 );

	return 0;
}

