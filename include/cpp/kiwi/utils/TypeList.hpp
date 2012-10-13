
#ifndef KIWI_UTILS_TYPELIST_HPP
#define KIWI_UTILS_TYPELIST_HPP

namespace kiwi {

struct Null_t {};

struct EmptyTypeList
{
    typedef Null_t Type;
    typedef Null_t Tail;
    enum { Size = 0 };
};

template<typename T, typename Tail_> struct TypeList
{
    typedef typename Tail_ Tail;
    typedef typename T Type;
    enum { Size = Tail::Size +1 };
};

template<typename ATypeList, int N> struct TypeListGet
{
    typedef typename TypeListGet<ATypeList::Tail, N-1>::Result Type;
};

template<typename ATypeList> struct TypeListGet<ATypeList, 0>
{
    typedef typename ATypeList::Type Type;
};


template<typename ATypeList> struct Tuple
{
    typedef typename ATypeList TypeList;
    enum { Size = TypeList::Size };

    TypeList::Type data;
    TypeTuple<typename TypeList::Tail> tail;
};

template<> struct Tuple<EmptyTypeList>
{
    enum { Size = 0 };
};

template<typename ATuple, int N> 
typename TypeListGet<typename ATuple::TypeList, N>::Type tupleGet(ATuple& tuple)
{
    return tupleGet<N-1>(tuple.tail);
}

template<typename ATuple> 
typename ATuple::Type tupleGet<ATuple, 0>(ATuple& tuple)
{
    return tuple.data;
}


} // namespace

#endif
