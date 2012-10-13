
#ifndef KIWI_PROCESSING_FUNCTIONWRAPPER_HPP
#define KIWI_PROCESSING_FUNCTIONWRAPPER_HPP

namespace kiwi {
namespace processing {

struct InvalidType {};

template<typename Array, int N> struct TypedArrayGet {
    typedef InvalidType Result;
};
template<> struct TypedArrayGet<0> { typedef typename Array::Type0 Result; };
template<> struct TypedArrayGet<1> { typedef typename Array::Type1 Result; };
template<> struct TypedArrayGet<2> { typedef typename Array::Type2 Result; };
template<> struct TypedArrayGet<3> { typedef typename Array::Type3 Result; };
template<> struct TypedArrayGet<4> { typedef typename Array::Type4 Result; };


struct TypeArray0 {
    enum {Size = 0};
};

template<typename T> struct TypeArray1 {
    typedef T Type0;
    enum {Size = 1};
};
template<typename T0, typename T1> struct TypeArray2 {
    typedef T0 Type0;
    typedef T1 Type1;
    enum {Size = 2};
};
template<typename T0, typename T1, typename T2> struct TypeArray3 {
    typedef T0 Type0;
    typedef T1 Type1;
    typedef T2 Type2;
    enum {Size = 3};
};
template<typename T0, typename T1, typename T2, typename T3> struct TypeArray4 {
    typedef T0 Type0;
    typedef T1 Type1;
    typedef T2 Type2;
    typedef T2 Type3;
    enum {Size = 4};
};
template<typename T0, typename T1, typename T2, typename T3, typename T4> struct TypeArray5 {
    typedef T0 Type0;
    typedef T1 Type1;
    typedef T2 Type2;
    typedef T2 Type3;
    typedef T2 Type4;
    enum {Size = 5};
};

template

template<typename InputTypeArray, typename OutputTypeArray>
class FunctionWrapper {
public:
    virtual void process(StackFrame* s) {
        
    }

    DataIndex[InputTypeArray::Size] inputs;
    DataIndex[OutputTypeArray::Size] outputs;
};

} // namespace
} // namespace

#endif
