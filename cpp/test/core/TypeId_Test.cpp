
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/TypeId.hpp"
#include "kiwi/utils/TypeIdHelper.hpp"


using namespace kiwi;


template <typename T> void TestTypeEqual()
{
    T a, b;
    const T ca = a;
    volatile T va;
    
    KIWI_TEST_EQUAL("a and b have same types.", kiwi::core::TypeOf(a), kiwi::core::TypeOf(b));
    KIWI_TEST_EQUAL("T and const T have same type ids.", kiwi::core::TypeOf(a), kiwi::core::TypeOf(ca));
    KIWI_TEST_EQUAL("T and colatile T have same type ids.", kiwi::core::TypeOf(a), kiwi::core::TypeOf(va));
    KIWI_TEST("A type id is never zero.", kiwi::core::TypeOf<T>() != 0);
}


template <typename T1, typename T2> void TestTypeDifferent()
{
    KIWI_TEST("T1 and T2 have different type ids", kiwi::core::TypeOf<T1>() != kiwi::core::TypeOf<T2>() );
}

struct TestStruct1{};

int main()
{
    KIWI_BEGIN_TESTING("Kiwi::core::TypeId");

    TestTypeEqual<int>();
    TestTypeEqual<float>();
    TestTypeEqual<char>();
    TestTypeEqual<TestStruct1>();

    TestTypeDifferent<int,float>();
    TestTypeDifferent<int,char>();
    TestTypeDifferent<TestStruct1,char>();
    TestTypeDifferent<float,double>();

    kiwi::utils::RegisterTypeIdName( kiwi::core::TypeOf<int>(), "int" );
    kiwi::utils::RegisterTypeIdName( kiwi::core::TypeOf<float>(), "float" );
    kiwi::utils::RegisterTypeIdName( kiwi::core::TypeOf<char>(), "char" );
    kiwi::utils::RegisterTypeIdName( kiwi::core::TypeOf<TestStruct1>(), "TestStruct1" );

    KIWI_TEST("type id name helper (int)", kiwi::utils::TypeIdName(kiwi::core::TypeOf<int>()) == string("int") );
    KIWI_TEST("type id name helper (float)", kiwi::utils::TypeIdName(kiwi::core::TypeOf<float>()) == string("float") );
    KIWI_TEST("type id name helper (unknown)", kiwi::utils::TypeIdName(kiwi::core::TypeOf<double>()) == string("UnknownType") );
    log << utils::TypeIdName(kiwi::core::TypeOf<double>()) << endl;
    KIWI_TEST("type id name helper (TestStruct1)", kiwi::utils::TypeIdName(kiwi::core::TypeOf<TestStruct1>()) == string("TestStruct1") );
    
    return KIWI_END_TESTING;
}
