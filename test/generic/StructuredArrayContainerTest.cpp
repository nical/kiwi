#include "kiwi/generic/StructuredArrayContainer.hpp"

using namespace kiwi;
using namespace kiwi::generic;


template<typename T, kiwi::uint32_t D>
void test()
{
	typedef kiwi::generic::StructuredArrayContainer<T, D> Array;
	typedef typename Array::CoordinateVector CoordinateVector;

	Array array1(CoordinateVector::cube(100), "[R|G|B|A]");
	Array array2(CoordinateVector::cube(100), "[R%G%B%A]");
	Array array3(CoordinateVector::cube(100), "[R%G%B|A]");
	Array array4(CoordinateVector::cube(100), "[%|%]");

	assert( array1.isComposite() );
	assert( array2.isComposite() );
	assert( array3.isComposite() );

	assert(array1.layout() == 0);
	assert(array2.layout() == 7);
	assert(array3.layout() == 3);
	assert(array4.layout() == 5);

	Debug::print() << "array1.nbSubContainers: "<< array1.nbSubContainers() << endl();
	Debug::print() << "array2.nbSubContainers: "<< array2.nbSubContainers() << endl();
	Debug::print() << "array3.nbSubContainers: "<< array3.nbSubContainers() << endl();
	Debug::print() << "array4.nbSubContainers: "<< array4.nbSubContainers() << endl();
	assert( array1.nbSubContainers() == 4);
	assert( array2.nbSubContainers() == 4);
	assert( array3.nbSubContainers() == 4);
	assert( array4.nbSubContainers() == 4);
}

void test2()
{
	// ---------------------------- first test, without interleaved arrays
	
	typedef kiwi::generic::StructuredArrayContainer<kiwi::uint8_t, 3> Array;
	typedef kiwi::generic::ArrayContainer<kiwi::uint8_t, 3> SubArray;
	typedef Array::CoordinateVector CoordinateVector;
	
	Array array1(CoordinateVector(5,10,4), "[R|G|B|A]");
	assert(array1.layout() == 0);

	assert( array1.nbSubContainers() == 4);

	SubArray* subArray0 =  (SubArray*)array1.subContainer(0);
	SubArray* subArray1 =  (SubArray*)array1.subContainer(1);
	SubArray* subArray2 =  (SubArray*)array1.subContainer(2);
	SubArray* subArray3 =  (SubArray*)array1.subContainer(3);
	
	CoordinateVector expectedStride(1,5,50);

	assert(subArray0 != 0);

	Debug::print() << "expected stride: " << expectedStride.toStr() << endl();
	Debug::print() << "actual stride: " << subArray0->stride().toStr() << endl();
	
	assert(subArray0->stride() == expectedStride);
	assert(subArray1->stride() == expectedStride);
	assert(subArray2->stride() == expectedStride);
	assert(subArray3->stride() == expectedStride);
	
	assert(subArray0->spanSize() == CoordinateVector(5,10,4));
	assert(subArray1->spanSize() == CoordinateVector(5,10,4));
	assert(subArray2->spanSize() == CoordinateVector(5,10,4));
	assert(subArray3->spanSize() == CoordinateVector(5,10,4));

	kiwi::uint8_t* mainDataPtr = array1.getDataPointer();
	assert(subArray0->getDataPointer() >= mainDataPtr );
	assert(subArray1->getDataPointer() >= mainDataPtr );
	assert(subArray2->getDataPointer() >= mainDataPtr );
	assert(subArray3->getDataPointer() >= mainDataPtr );
	assert(subArray0->getDataPointer() < mainDataPtr+array1.size() );
	assert(subArray1->getDataPointer() < mainDataPtr+array1.size() );
	assert(subArray2->getDataPointer() < mainDataPtr+array1.size() );
	assert(subArray3->getDataPointer() < mainDataPtr+array1.size() );

	// ---------------------------- second test, with interleaved arrays

	Array array2(CoordinateVector(5,10,4), "[R%G%B|A]");
	assert( array2.layout() == 3 );

	assert( array2.nbSubContainers() == 4 );

	SubArray* subArray2_0 = (SubArray*)array2.subContainer(0);
	SubArray* subArray2_1 = (SubArray*)array2.subContainer(1);
	SubArray* subArray2_2 = (SubArray*)array2.subContainer(2);
	SubArray* subArray2_3 = (SubArray*)array2.subContainer(3);

	expectedStride = CoordinateVector(3,15,150);
	mainDataPtr = array2.getDataPointer();

	assert(subArray2_0 != 0);

	Debug::print() << "expected stride: " << expectedStride.toStr() << endl();
	Debug::print() << "actual stride: " << subArray2_0->stride().toStr() << endl();

	assert(subArray2_0->stride() == expectedStride);
	assert(subArray2_1->stride() == expectedStride);
	assert(subArray2_2->stride() == expectedStride);

	assert(subArray2_0->getDataPointer() >= mainDataPtr );
	assert(subArray2_1->getDataPointer() >= mainDataPtr );
	assert(subArray2_2->getDataPointer() >= mainDataPtr );
	assert(subArray2_3->getDataPointer() >= mainDataPtr );
	assert(subArray2_0->getDataPointer() < mainDataPtr+array1.size() );
	assert(subArray2_1->getDataPointer() < mainDataPtr+array1.size() );
	assert(subArray2_2->getDataPointer() < mainDataPtr+array1.size() );
	assert(subArray2_3->getDataPointer() < mainDataPtr+array1.size() );
	
}

void test3()
{
	typedef kiwi::generic::StructuredArrayContainer<kiwi::uint8_t, 2> Array;
	typedef kiwi::generic::ArrayContainer<kiwi::uint8_t, 2> SubArray;
	typedef Array::CoordinateVector CoordinateVector;
	
	Array array1(CoordinateVector(5,5), "[R|G|B]");
	assert(array1.layout() == 0);

	SubArray* R = (SubArray*)array1.subContainer(0);
	SubArray* G = (SubArray*)array1.subContainer(1);
	SubArray* B = (SubArray*)array1.subContainer(2);

	assert(R->getDataPointer() == array1.getDataPointer() );
	assert(G->getDataPointer() == array1.getDataPointer()+25 );
	assert(B->getDataPointer() == array1.getDataPointer()+50 );

	kiwi::uint8_t* dataPtr = array1.getDataPointer();	
	for(kiwi::uint32_t i = 0; i < array1.size(); ++i){
		*(dataPtr + i) = 0;
	}

	for(kiwi::uint32_t i = 0; i < R->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < R->spanSize(1); ++j){
			R->setValue(CoordinateVector(i,j), 1 );
		}
	for(kiwi::uint32_t i = 0; i < G->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < G->spanSize(1); ++j){
			G->setValue(CoordinateVector(i,j), 2 );
		}
	for(kiwi::uint32_t i = 0; i < B->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < B->spanSize(1); ++j){
			B->setValue(CoordinateVector(i,j), 4 );
		}
		
	for(kiwi::uint32_t i = 0; i < array1.size(); ++i){
		Debug::print() << static_cast<int>(*(dataPtr + i));
	}
	Debug::print() << endl();

	// ---------------------------------------------

	Array array2(CoordinateVector(5,5), "[R|G%B|A]");
	assert(array2.layout() == 2);

	SubArray* R2 = (SubArray*)array2.subContainer(0);
	SubArray* G2 = (SubArray*)array2.subContainer(1);
	SubArray* B2 = (SubArray*)array2.subContainer(2);
	SubArray* A2 = (SubArray*)array2.subContainer(3);

	assert(R2->getDataPointer() == array2.getDataPointer() );
	assert(G2->getDataPointer() == array2.getDataPointer()+25 );
	assert(B2->getDataPointer() == array2.getDataPointer()+26 );
	assert(A2->getDataPointer() == array2.getDataPointer()+75 );

	dataPtr = array2.getDataPointer();	
	for(kiwi::uint32_t i = 0; i < array2.size(); ++i){
		*(dataPtr + i) = 0;
	}

	for(kiwi::uint32_t i = 0; i < R2->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < R2->spanSize(1); ++j){
			R2->setValue(CoordinateVector(i,j), 1 );
		}
	for(kiwi::uint32_t i = 0; i < G2->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < G2->spanSize(1); ++j){
			G2->setValue(CoordinateVector(i,j), 2 );
		}
	for(kiwi::uint32_t i = 0; i < B2->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < B2->spanSize(1); ++j){
			B2->setValue(CoordinateVector(i,j), 4 );
		}
	for(kiwi::uint32_t i = 0; i < A2->spanSize(0); ++i)
		for(kiwi::uint32_t j = 0; j < A2->spanSize(1); ++j){
			A2->setValue(CoordinateVector(i,j), 8 );
		}
		
	for(kiwi::uint32_t i = 0; i < array2.size(); ++i){
		Debug::print() << static_cast<int>(*(dataPtr + i));
	}
	Debug::print() << endl();
		
}

int main()
{
ScopedBlockMacro(__, "StructuredArrayContainer::Test")

	test<kiwi::uint8_t,2>();
	test<kiwi::float_t,1>();
	test<kiwi::int32_t,3>();

	test2();

	test3();

}
