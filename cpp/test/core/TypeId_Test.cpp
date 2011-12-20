#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/TypeIndex.hpp"
#include "kiwi/utils/TypeIdHelper.hpp"
#include "kiwi/core/DataTypeId.hpp"


using namespace kiwi;
using namespace kiwi::core;



template <typename T> void TestTypeEqual()
{
    typedef T AliasT;
    DataTypeId a  = DataTypeId::TypeOf<T>();
    DataTypeId b  = DataTypeId::TypeOf<T>();
    DataTypeId aa = DataTypeId::TypeOf<AliasT>();
    DataTypeId ca = DataTypeId::TypeOf<const T>();
    DataTypeId va = DataTypeId::TypeOf<volatile T>();
    DataTypeId n; // null data type id
    
    KIWI_TEST("a and b have same types.", a == b );
    KIWI_TEST("typedef should not alter the type.", a == aa );
    KIWI_TEST("T and const T have same type ids.", a == ca );
    KIWI_TEST("T and colatile T have same type ids.", a == va );
    KIWI_TEST("Different from nullTypeId.", a != n );
    KIWI_TEST("Different from nullTypeId.", n == DataTypeId::NullType() );
}


template <typename T1, typename T2> void TestTypeDifferent()
{
    KIWI_TEST("T1 and T2 have different type ids", DataTypeId::TypeOf<T1>() != DataTypeId::TypeOf<T2>() );
}

struct TestStruct1{};

    

int main()
{
	KIWI_BEGIN_TESTING("Kiwi::core::DataTypeId");

    TestTypeEqual<int>();
    TestTypeEqual<float>();
    TestTypeEqual<char>();
    TestTypeEqual<TestStruct1>();

    TestTypeDifferent<int,float>();
    TestTypeDifferent<int,char>();
    TestTypeDifferent<TestStruct1,char>();
    TestTypeDifferent<float,double>();

    auto id_int1 = DataTypeId::TypeOf<int>();
    auto id_int2 = DataTypeId::TypeOf<int>();
    auto id_float1 = DataTypeId::TypeOf<float>();
    auto id_float2 = DataTypeId::TypeOf<float>();

    auto id_intCopy = id_int1;
    
    KIWI_TEST("Equality of two static types (int)", id_int1 == id_int2);
    KIWI_TEST("Equality of two static types (float)", id_float1 == id_float2);
    KIWI_TEST("float != int", id_float1 != id_int1);
    KIWI_TEST("Copy", id_intCopy == id_int1);
    KIWI_TEST("isStaticType", id_intCopy.isStaticType());
    KIWI_TEST("!isRuntimeType", !id_intCopy.isRuntimeType());

    return KIWI_END_TESTING;
}


/*
    kiwi::utils::RegisterTypeIdName( kiwi::core::TypeOf<int>(), "int" );
    kiwi::utils::RegisterTypeIdName( kiwi::core::TypeOf<float>(), "float" );
    kiwi::utils::RegisterTypeIdName( kiwi::core::TypeOf<char>(), "char" );
    kiwi::utils::RegisterTypeIdName( kiwi::core::TypeOf<TestStruct1>(), "TestStruct1" );

    KIWI_TEST("type id name helper (int)", kiwi::utils::TypeIdName(kiwi::core::TypeOf<int>()) == string("int") );
    KIWI_TEST("type id name helper (float)", kiwi::utils::TypeIdName(kiwi::core::TypeOf<float>()) == string("float") );
    KIWI_TEST("type id name helper (unknown)", kiwi::utils::TypeIdName(kiwi::core::TypeOf<double>()) == string("UnknownType") );
    log << utils::TypeIdName(kiwi::core::TypeOf<double>()) << endl;
    KIWI_TEST("type id name helper (TestStruct1)", kiwi::utils::TypeIdName(kiwi::core::TypeOf<TestStruct1>()) == string("TestStruct1") );
*/

