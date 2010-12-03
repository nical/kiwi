#include "kiwi/core/Commons.hpp"
#include "kiwi/generic/Point.hpp"

#include "generic/PointTest.hpp"
#include "core/FilterTest.hpp"
#include "generic/ArrayContainerTest.hpp"
#include "generic/MultiArrayContainerTest.hpp"
#include "generic/ValueContainerTest.hpp"
#include "core/MetaFilterTest.hpp"
#include "image/CairoImageContainerTest.hpp"
#include "pipeline/SimplePipelineTest.cpp"
#include "image/ContrastTest.hpp"
#include "text/TextContainerTest.hpp"
#include "core/NodeTest.hpp"
#include "core/FactoryTest.hpp"


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
		
		Debug::print() << "end of the test suite" << endl();
		

}
