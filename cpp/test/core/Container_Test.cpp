
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/DebugStream.hpp"

#include <assert.h>

using namespace kiwi;
using namespace kiwi::core;



class TestData
{
public:
    int get(){ return 42; }
};

Data* NewTestData(){ return new Container<TestData>; }
namespace kiwi{
namespace user{
template<> struct DataTrait<TestData>
{
public:
    static const char* Name() { return "TestData"; }
};
}//namespace
}//namespace

int main()
{
    KIWI_BEGIN_TESTING("Kiwi::core::Node Test");
    
    const DataTypeInfo* info  = kiwi::core::RegisterDataType("TestData", &NewTestData );

    assert( info->name() == string(kiwi::user::DataTrait<TestData>::Name()) );
    
    return KIWI_END_TESTING;
}
