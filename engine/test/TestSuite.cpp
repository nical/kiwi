#include "core/Commons.hpp"

#include "generic/PointTest.hpp"
#include "core/FilterTest.hpp"
#include "generic/ArrayContainerTest.hpp"
#include "generic/MultiArrayContainerTest.hpp"
#include "core/MetaFilterTest.hpp"
//#include "audio/AudioBufferTest.hpp"
//#include "text/StringContainerTest.hpp"



int main()
{
	ScopedBlockMacro(__scop, "kiwi::TestSuite")
	
		PointTest<char,2>();
		PointTest<float,3>();
		PointTest<double,4>();
		PointTest<unsigned int,3>();
		
		debug.endl(3);
		debug.print() << "------------------------------------------------"
					<< "Point Test Ok" << endl();
	
	
		ArrayContainerTest<int, 2, 2>();
		debug.print() << "----------------------------------------------"
		<< endl();
		debug.print() << "----------------------------------------------"
		<< endl();
		ArrayContainerTest<float, 2, 2>();
		debug.print() << "----------------------------------------------"
		<< endl();
		ArrayContainerTest<unsigned int, 1, 2>();
		debug.print() << "----------------------------------------------"
		<< endl();
		debug.print() << "----------------------------------------------"
		<< endl();
		ArrayContainerTest<double, 3, 4>();
		debug.print() << "----------------------------------------------"
		<< endl();
		ArrayContainerTest<long int, 5, 2>();
	
		debug.endl(3);
		debug.print() << "----------------------------------------------"
					<< "ArrayContainer Test Ok" << endl();
		debug.endl(3);
		
		MultiArrayContainerTest<int, 2, 2>();
		debug.print() << "----------------------------------------------"
		<< endl();
		
		MultiArrayContainerTest<double, 3, 4>();
		debug.print() << "----------------------------------------------"
		<< endl();
		
		debug.endl(3);
		debug.print() << "----------------------------------------------"
					<< "MultiArrayContainer Test Ok" << endl();
		debug.endl(3);
		
		
		MetaFilterTest<int, 2 ,2>();

}
