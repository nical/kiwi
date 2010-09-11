#include "Point.hpp"
#include "ArrayImageContainer.hpp"
#include <iostream>

using namespace std;

int main()
{

	
	kiwi::Point<int,2> p(1,5);

	cerr << p.coordinate(0)<<endl;



return 0;
}
