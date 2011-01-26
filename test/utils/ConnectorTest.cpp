
#include <assert.h>
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/Connector.hpp"

using namespace kiwi::utils;

class A;
class B;
class C;
class D;
class E;
class F; // TODO
class G;

class A : public Connector<A, B, 5>{};
class B : public Connector<B, A, 2>{};
class C : public Connector<C, D, 2>, public Connector<C, E, 6>
{
public:
	typedef Connector<C, D, 2> Connector1;
	typedef Connector<C, E, 6> Connector2;
} ;
class D : public Connector<D, C, 1>{};
class E : public Connector<E, C, 4>{};

class F : public Connector<F, G, 1>{};
class G : public Connector<G, F, 3>{};

using namespace kiwi;

int main(){
	ScopedBlockMacro(__scop, "Connector::Test")
	A a1, a2, a3;
	B b1, b2, b3;
	C c1;
	D d1;
	E e1;

	a1.connect(&b1);

	assert( a1.nbConnections() == 1 );
	assert( b1.nbConnections() == 1 );
	
	a1.connect(&b2);

	assert( a1.nbConnections() == 2 );
	assert( b1.nbConnections() == 1 );
	
	assert( a1.connectedInstance(0) == &b1);
	assert( b1.connectedInstance(0) == &a1);
	assert( b2.connectedInstance(0) == &a1);
	assert( a1.connectedInstance(1) == &b2);

	assert( b1.connectedInstance(1) == 0 );
	b1.connect(&a2);
	assert( !b1.canConnect() );
	b1.connect(&a3);
	assert( b1.nbConnections() == 2 );

	a1.disconnect(&b1);
	assert( a1.nbConnections() == 1 );
	assert( b1.nbConnections() == 1 );

	Debug::print() << " test: multi-connector" << endl();
	// ------------ multi-connector

	c1.Connector1::connect(&d1);
	c1.Connector2::connect(&e1);
	assert( c1.Connector1::nbConnections() == 1 );
	assert( c1.Connector2::nbConnections() == 1 );
	assert( d1.nbConnections() == 1 );
	assert( e1.nbConnections() == 1 );

	Debug::print() << " test: One to many" << endl();
	// ------------ one connection

	F f1;
	G g1, g2;
	assert( f1.nbConnections() == 0 );
	assert( f1.canConnect() );
	
	f1.connect(&g1);
	assert( f1.nbConnections() == 1 );
	assert( !f1.canConnect() );
	assert( f1.connectedInstance() == &g1 ); 
	
	f1.connect(&g2); // should not work
	assert( f1.nbConnections() == 1 );
	assert( f1.connectedInstance() == &g1 );
	g2.connect(&f1); // should not work
	assert( f1.nbConnections() == 1 );
	assert( g2.nbConnections() == 0 );
	assert( f1.connectedInstance() == &g1 );

	// then again, this should not disconnect anything as g2 should not
	// be connected.
	f1.disconnect( &g2 );
	assert( f1.nbConnections() == 1 );
	assert( f1.connectedInstance() == &g1 );
	

	// now let's try to disconnect g1, it should work
	f1.disconnect( &g1 );
	assert( f1.connectedInstance() == 0 );
	assert( f1.nbConnections() == 0 );
	assert( f1.canConnect() );
	f1.connect( &g1 );
	assert( f1.nbConnections() == 1 );
	f1.disconnect();
	
	assert( f1.nbConnections() == 0 );
	assert( g1.nbConnections() == 0 );
	assert( f1.canConnect() );
	assert( g1.canConnect() );
	g1.connect( &f1 );
	assert( f1.nbConnections() == 1 );
	assert( g1.nbConnections() == 1 );
	g1.disconnect();
	assert( f1.nbConnections() == 0 );
	assert( g1.nbConnections() == 0 );
	
	
	
}
