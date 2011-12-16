#include "kiwi/utils/Testing.hpp"

#include "kiwi/core/DataTypeId.hpp"


using namespace kiwi;
using namespace kiwi::core;


int main()
{
	KIWI_BEGIN_TESTING("Kiwi::core::DataTypeId");

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
