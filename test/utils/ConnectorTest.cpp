
#include <assert.h>
#include "kiwi/utils/Connector.hpp"

class A;
class B;
class C;
class D;
class E;

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

int main(){
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
	assert( b1.nbConnections() == 0 );

	// ------------ multi-connector

	c1.Connector1::connect(&d1);
	c1.Connector2::connect(&e1);
	assert( c1.Connector1::nbConnections() == 1 );
	assert( c1.Connector2::nbConnections() == 1 );
	assert( d1.nbConnections() == 1 );
	assert( e1.nbConnections() == 1 );
	
}
