
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/utils/DebugStream.hpp"


using namespace kiwi;
using namespace kiwi::core;



class TestData1
{
public:
    int get(){ return 42; }
};

class TestData2
{
public:
    int get(){ return 1337; }
};

KIWI_DECLARE_CONTAINER_AND_NAME(TestData1)
KIWI_DECLARE_CONTAINER_AND_NAME(TestData2)
KIWI_DECLARE_CONTAINER(int,"Int")
KIWI_DECLARE_CONTAINER(float,"Float")

int main()
{
    KIWI_BEGIN_TESTING("Kiwi::core::Container");
    
    auto info1  = DataTypeManager::RegisterDataType("TestData1", &NewTestData1 );
    auto info2  = DataTypeManager::RegisterDataType("TestData2", &NewTestData2 );
    auto infoi  = DataTypeManager::RegisterDataType("Int", &Newint );
    auto infof  = DataTypeManager::RegisterDataType("Float", &Newfloat );

    KIWI_TEST( "type info name check 1.", info1->name() == string("TestData1") );
    KIWI_TEST( "type info name check 2.", info2->name() == string("TestData2") );
    KIWI_TEST( "type info name check Int.", infoi->name() == string("Int") );
    KIWI_TEST( "type info name check Float.", infof->name() == string("Float") );

    auto td1 = DataTypeManager::Create("TestData1");
    KIWI_TEST( "Instanciate known data 1 type not null.", td1 != 0);
    KIWI_TEST( "Instanciated type 1 name.", td1->type() == info1 );
    auto td2 = DataTypeManager::Create("TestData2");
    KIWI_TEST( "Instanciate known data 2 type not null.", td2 != 0);
    KIWI_TEST( "Instanciated type 2 name.", td2->type() == info2 );
    auto tdx = DataTypeManager::Create("SomeUnknownType");
    KIWI_TEST( "Instanciate unknown data 2 type returns null.", tdx == 0);

    auto tdi = DataTypeManager::Create("Int");
    *tdi->value<int>() = 42;

    KIWI_TEST( "Container value assignment.", *tdi->value<int>() == 42);
    auto intContainerNode = NodeTypeManager::Create("Int");
    KIWI_TEST( "creation of a container node.", intContainerNode != 0 );
    
    
    delete td1;
    delete td2;
    delete tdx;
    delete tdi;
    delete intContainerNode;
    return KIWI_END_TESTING;
}
