#include "FilterSkeleton.hpp"

#include "kiwi/generic/Point.hpp"

namespace kiwi{
namespace tutorial{




FilterExample::FilterExample()
: CanonicalFilter( 1 /*one writer input*/)
{
ScopedBlockMacro(scp_block, "FilterExample::constructor");
	// CanonicalFilter's constructor automatically adds one reader output port
	// and one writer input port.
	
	addReaderInputPort(); //reader input 0
	addReaderInputPort(); //reader input 1
}




void FilterExample::process()
{
	// a macro that creates an indentation block and closes it automatically
	// at the end of the scop.
	ScopedBlockMacro(proc_block, "AddArraysFilter::process()");

	Debug::print() << "Allocate Reader #0" << endl();
	myReader A( readerInputPort(0) );
	
	Debug::print() << "Allocate Reader #1" << endl();
	myReader B( readerInputPort(1) );
	
	Debug::print() << "Allocate Writer #0" << endl();
	myWriter result( writerInputPort(0) );
	
	Debug::beginBlock( "compute..");// macro that indents the terminal's output
	
	// you can use kiwi::generic::Point<T,D> to access data in ArrayContainers...
	Point<int, Dimension> pos(0);
	result.set( pos , A.get( pos ) + B.get( pos ) );
	
	// or use iterators...
	ArrayConstIterator<ValueType> itA = A.getIterator();
	ArrayConstIterator<ValueType> itB = B.getIterator();
	ArrayIterator<ValueType> itResult = result.getIterator();
	
	do
	{
		if( itA.isDone() ) break;
		if( itB.isDone() ) break;

		// do stuff...
		*itResult = *itA + *itB; 
		
		++itA ;
		++itB ;
	} while(itResult.onIteration() );
	
	Debug::endBlock( "compute.."); // close the indentation block
	
	return;
}


bool FilterExample::readyCondition()
{
	return (readerInputPort(0).isConnected()
		&& readerInputPort(1).isConnected()
		&& writerInputPort(0).isConnected() );
}









}//namespace
}//namespace
