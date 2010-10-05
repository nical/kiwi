#include "generic/Point.hpp"
#include "core/Commons.hpp"
#include <assert.h>
#include <cppunit/ui/text/TestRunner.h>

/*

template<typename ValueType, unsigned Dimension>
class PointTest : public CppUnit::TestFixture 
{ 
public: 
	typedef Point<ValueType,Dimension> Point_t;

  PointTest( std::string name ) : CppUnit::TestCase( name ) {}
  
  void setUp()
  {
  }

  void tearDown() 
  {
  }
  
  void testConstructor() 
  {
	Point_t A(0);
	Point_t B(A);
	Point_t C = A;
	
	bool test1 = true;
	for(unsigned i = 0; i < Dimension; ++i) if(A(i) != 0) test1 = false;
    CPPUNIT_ASSERT( test1 );
    
    bool test2 = true;
	for(unsigned i = 0; i < Dimension; ++i) if(B(i) != 0) test2 = false;
    CPPUNIT_ASSERT( test2 );
    
    bool test3 = true;
	for(unsigned i = 0; i < Dimension; ++i) if(C(i) != 0) test3 = false;
    CPPUNIT_ASSERT( test3 );
  }
  
  public: 
  static* suite()
  {
	CppUnit::TestSuite *testsuite = new suite;
	
	testsuite->addTest( new CppUnit::TestCaller<TestClass>(
                       "testConstructor", 
                       &TestClass::testConstructor ) );
	testsuite->addTest( new CppUnit::TestCaller<TestClass>(
                       "testEquality", 
                       &TestClass::testEquality ) );
	return return testSuite;
  }
  
};

template<typename TestClass> void testSuite()
{
	
	//suite.run( &result );


	CppUnit::TextUi::TestRunner runner;

	runner.addTest( TestClass::suite() );
	
	runner.run();

}

*/


using namespace kiwi;
int main()
{

typedef kiwi::generic::Point<int,2> point2D;

ScopedBlockMacro(__scop, "kiwi::TestPoint");
	
	point2D p1(1,5);
	point2D p2(42,-4);
	point2D p3(43,1);
	point2D zero(0);
	point2D copy(p3);
	point2D eq = p1;
	

	assert(p1 != p2);
	assert(p1+p2 == p3);
	assert(p1-p1 == zero);
	assert(p1 == p1);
	assert(p2 == p2);
	assert(eq == p1);
	assert(copy == p3);

	for(unsigned i = 0; i < 2; ++i) assert( p2[i]==p2(i) );
	
	debug.print() << " Point test suite success " << endl();

	//testSuite< PointTest<float, 3> >();
	
	//testSuite< PointTest<unsigned, 4> >();


return 0;
}
