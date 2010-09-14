#include "../src/image/Point.hpp"
#include "../src/core/Commons.hpp"

using namespace std;

int main()
{

ScopedBlockMacro(s1, "kiwi::TestPoint");
	
	kiwi::image::Point<int,2> p(1,5);

	debug.print() << p.coordinate(0)<<endl;



return 0;
}
