

#include "kiwi/generic/PointVectorContainer.hpp"

using namespace kiwi::generic;
using namespace kiwi;

void PointVectorContainerTest()
{
	ScopedBlockMacro("PointVectorContainer::Test")

	typedef int ValueType;
	typedef PointVectorContainer<ValueType,3> PointContainer;
	typedef PointContainer::PointType PointType;
	typedef NumberContainerInterface<ValueType> ValueContainer;

	
	PointContainer point( PointType(1,2,3) );
	
	assert( point.isComposite() );
	assert( point.nbSubContainers() == 3 );
	
	ValueContainer* v1 = dynamic_cast<ValueContainer*>(point.subContainer(0) );
	ValueContainer* v2 = dynamic_cast<ValueContainer*>(point.subContainer(1) );
	ValueContainer* v3 = dynamic_cast<ValueContainer*>(point.subContainer(2) );

	assert( v1 );
	assert( v2 );
	assert( v3 );

	assert( v1->getValue() == 1 );
	assert( v2->getValue() == 2 );
	assert( v3->getValue() == 3 );

	v1->setValue(42);
	v2->setValue(12);
	v3->setValue(24);

	assert( point == PointType(42,12,24) );
}


int main()
{
	PointVectorContainerTest();

}
