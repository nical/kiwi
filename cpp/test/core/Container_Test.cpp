
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
    SCOPEDBLOCK("Kiwi::core::Node Test");
    
    const DataTypeInfo* info  = kiwi::core::RegisterDataType("TestData", &NewTestData );

    assert( info->name() == string(kiwi::user::DataTrait<TestData>::Name()) );
    
    return 0;
}
