#include "kiwi/core/Commons.hpp"
#include "kiwi/generic/Point.hpp"

#include "generic/PointTest.cpp"
#include "core/FilterTest.cpp"
#include "generic/ArrayContainerTest.cpp"
#include "generic/MultiArrayContainerTest.cpp"
#include "generic/ValueContainerTest.cpp"
#include "core/MetaFilterTest.cpp"
#include "image/CairoImageContainerTest.cpp"
#include "pipeline/SimplePipelineTest.cpp"
#include "image/ContrastTest.cpp"
#include "text/TextContainerTest.Cpp"
#include "core/NodeTest.cpp"
#include "core/FactoryTest.cpp"
#include "utils/ModuloTest.cpp"


int main()
{
	Debug::init(false, false, 0);
	ScopedBlockMacro(__scop, "kiwi::TestSuite")
	
		PointTest<char,2>();
		PointTest<float,3>();
		PointTest<double,4>();
		PointTest<unsigned int,3>();
		
		Debug::endl(3);
		Debug::print() << "------------------------------------------------"
					<< "Point Test Ok" << endl();
	
	
		ArrayContainerTest<int, 2, 2>();
		Debug::print() << "----------------------------------------------"
		<< endl();
		Debug::print() << "----------------------------------------------"
		<< endl();
		ArrayContainerTest<float, 2, 2>();
		Debug::print() << "----------------------------------------------"
		<< endl();
		ArrayContainerTest<unsigned int, 1, 2>();
		Debug::print() << "----------------------------------------------"
		<< endl();
		Debug::print() << "----------------------------------------------"
		<< endl();
		ArrayContainerTest<double, 3, 4>();
		Debug::print() << "----------------------------------------------"
		<< endl();
		ArrayContainerTest<long int, 5, 2>();
	
		Debug::endl(3);
		Debug::print() << "----------------------------------------------"
					<< "ArrayContainer Test Ok" << endl();
		Debug::endl(3);
		
		MultiArrayContainerTest<int, 2, 2>();
		Debug::print() << "----------------------------------------------"
		<< endl();
		
		ValueContainerTest<double>();
		Debug::print() << "----------------------------------------------"
		<< endl();
		
		ValueContainerTest<char>();
		Debug::print() << "----------------------------------------------"
		<< endl();
		
		MultiArrayContainerTest<double, 3, 4>();
		Debug::print() << "----------------------------------------------"
		<< endl();
		
		Debug::endl(3);
		Debug::print() << "----------------------------------------------"
					<< "MultiArrayContainer Test Ok" << endl();
		Debug::endl(3);
		
		
		MetaFilterTest<int, 2 ,2>();

		Debug::endl(3);
		Debug::print() << "----------------------------------------------"
					<< "MetaFilter Test Ok" << endl();
		Debug::endl(3);

		
		CairoImageContainerTest();		


		Debug::endl(3);
		Debug::print() << "----------------------------------------------"
					<< "Cairo ImageContainer Test Ok" << endl();
		Debug::endl(3);

		SimplePipelineTest();

        Debug::endl(3);
		Debug::print() << "----------------------------------------------"
					<< "SimplePipeline Test Ok" << endl();
		Debug::endl(3);
		
		TextContainerTest();
		
        Debug::endl(3);
		Debug::print() << "----------------------------------------------"
					<< "TextContainer Test Ok" << endl();
		Debug::endl(3);

		NodeTest();
		FactoryTest();
		ModulotTest();
		
		Debug::print() << "end of the test suite" << endl();
		

}
