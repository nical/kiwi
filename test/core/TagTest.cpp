
#include "kiwi/core/Tags.hpp"

#include <assert.h>

using namespace kiwi;

int TagTest()
{
	ScopedBlockMacro(__scop__, "kiwi::Test::Tags");

	/* Test: Constructor with one tag.
	 * Scenario: Construct a tag with one token and check that the string returned
	 * by str() corresponds to the argument passed to the constructor.
	 */ 
	kiwi::Tags tag1("#text");
	assert(tag1.str() == kiwi::string("#text"));
	
	/* Test: Constructor with one tag.
	 * Scenario: Construct a tag with several tokens and check that the string 
	 * returned by str() corresponds to the argument passed to the constructor.
	 */ 
	kiwi::Tags tag2("#text#image#foo#bar");
	assert(tag2.str() == kiwi::string("#text#image#foo#bar") );
	assert(tag2.str(0) == kiwi::string("#text")  );
	assert(tag2.str(1) == kiwi::string("#image") );
	assert(tag2.str(2) == kiwi::string("#foo") );
	assert(tag2.str(3) == kiwi::string("#bar") );
	assert(Tags("#kiwi#kiwi") == Tags("#kiwi") ); 
	
	/* Test: equality ( operators == and != )
	 * Scenario: first check that two different tags anrent equal withs !=.
	 * Then check that tags are equal to themselves. Then verify that the result
	 * of == is always different than the one given by != on the same objects.
	 * Finally, check that the order doesn't chage the result with both operators.
	 */ 
	assert(tag1 != tag2); 
	assert(tag1 == tag1); 
	assert(tag2 == tag2); 
	assert((tag1==tag2) != (tag1!=tag2));
	assert((tag1==tag1) != (tag1!=tag1));
	assert((tag1==tag2) == (tag2==tag1));
	assert((tag1!=tag2) == (tag2!=tag1));
	assert(Tags("#foo#bar") == Tags("#bar#foo"));
	
	/* Test: Copy constroctor
	 * check the equality between the constructed Tags and its source.
	 */ 
	kiwi::Tags tagCopy1(tag1);
	kiwi::Tags tagCopy2(tag2);
	assert(tagCopy1 == tag1);
	assert(tagCopy2 == tag2);
	
	/* Test: Difference ( operators -= and - )
	 * Scenario: Compute tag2 - tag3 using both operators, check that the result
	 * is the one expected and that both results are equal. 
	 */ 	
	kiwi::Tags tag3("#text#foo");
	kiwi::Tags tag4 = tag2 - tag3;
	tag2 -= tag3;
	assert(tag2.str() == kiwi::string("#image#bar") );
	assert(tag2 == tag4);

	/* Test: union ( operators += and + )
	 * Scenario: Compute tag2 + tag3 using both operators, check that the result
	 * is the one expected and that both results are equal. 
	 */ 	
	assert((Tags("#foo#bar")+Tags("#bar#plop")) == Tags("#foo#bar#plop"));

	/* Test: number of tokens
	 * Scenario: check that the number of tags within each object is correct. 
	 * This test has to be run on objects that have and have not been modified 
	 * since construction. 
	 */ 
	assert(tag1.nb() == 1);
	assert(tag2.nb() == 2);
	assert(tag3.nb() == 2);
	assert(tag4.nb() == 2);


	Tags test("#kiwi#kiwi#foo#bar#plop");
	test &= Tags("#bar#foo");
	Debug::print() << "Test: " << test.str() << endl(); 

	/* Test: Intersection (operator &&) 
	 * Scenario: 
	 * 
	 */
	kiwi::Tags foobar("#foo#bar#plop#haha");
	kiwi::Tags foo("#foo#plop#hey");
	kiwi::Tags foo2("#foo#plop#hey");
	foo2 &= foobar;
	assert( (foo && foobar) == kiwi::Tags("#foo#plop") );
	assert( (foo && foobar) == (foobar && foo) );
	assert( (foo && foobar) == foo2 ); 

	/* Test: hasAll and hasOneOf methods 
	 * Scenario: 
	 * 
	 */
	assert( Tags("#foo#bar").hasAll( Tags("#foo#bar") ) );
	assert( !Tags("#foo#bar").hasAll( Tags("#foo#bar#plop") ) );
	assert( Tags("#foo#bar#plop#haha#kiwi").hasAll( Tags("#kiwi#foo#bar") ) );
	assert( Tags("#bar#foo#kiwi").hasAll( Tags("#kiwi#foo#bar") ) );
	assert( Tags("#bar#foo").hasOneOf( Tags("#kiwi#cpp#foo#bar") ) );
	assert( Tags("#foo").hasOneOf( Tags("#kiwi#cpp#foo#bar") ) );
	assert( ! Tags("#foo#bar#kiwi").hasOneOf( Tags("#cpp#d_lang#programming") ) );
	

	kiwi::Debug::print() << kiwi::endl() << "Tags Test: success !" << kiwi::endl();
	return 0;
}


int main()
{
	return TagTest();
}
