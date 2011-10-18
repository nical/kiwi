
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/core/Commons.hpp"
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

KIWI_DECLARE_CONTAINER_AND_NAME(TestData1);
KIWI_DECLARE_CONTAINER_AND_NAME(TestData2);
KIWI_DECLARE_CONTAINER(int,"Int");
KIWI_DECLARE_CONTAINER(float,"Float");

int main()
{
    KIWI_BEGIN_TESTING("Kiwi::core::Container");
    
    auto info1  = kiwi::core::RegisterDataType("TestData1", &NewTestData1 );
    auto info2  = kiwi::core::RegisterDataType("TestData2", &NewTestData2 );
    auto infoi  = kiwi::core::RegisterDataType("Int", &Newint );
    auto infof  = kiwi::core::RegisterDataType("Float", &Newfloat );

    KIWI_TEST( "type info name check 1.", info1->name() == string("TestData1") );
    KIWI_TEST( "type info name check 2.", info2->name() == string("TestData2") );
    KIWI_TEST( "type info name check Int.", infoi->name() == string("Int") );
    KIWI_TEST( "type info name check Float.", infof->name() == string("Float") );

    int a;
    KIWI_TEST( "DataTypeId equality.", DataTypeId<int>() == DataTypeId(a) );
    KIWI_TEST( "DataTypeId inequality.", DataTypeId<float>() != DataTypeId<char>() );
    KIWI_TEST( "DataTypeId equality and constness."
        , DataTypeId<const TestData1>() == DataTypeId<TestData1>() );

    auto td1 = InstanciateData("TestData1");
    KIWI_TEST( "Instanciate known data 1 type not null.", td1 != 0);
    KIWI_TEST( "Instanciated type 1 name.", td1->type() == info1 );
    auto td2 = InstanciateData("TestData2");
    KIWI_TEST( "Instanciate known data 2 type not null.", td2 != 0);
    KIWI_TEST( "Instanciated type 2 name.", td2->type() == info2 );
    auto tdx = InstanciateData("SomeUnknownType");
    KIWI_TEST( "Instanciate unknown data 2 type returns null.", tdx == 0);

    KIWI_TEST( "Data.DataTypeId 1 check", td1->dataTypeId() == DataTypeId<TestData1>() );
    KIWI_TEST( "Data.DataTypeId 2 check", td2->dataTypeId() == DataTypeId<TestData2>() );

    delete td1;
    delete td2;
    delete tdx;
    return KIWI_END_TESTING;
}
