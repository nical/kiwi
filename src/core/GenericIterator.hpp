#pragma once

#ifndef KIWI_IMAGE_HPP
#define KIWI_IMAGE_HPP


namespace kiwi
{
namespace core
{

/**
 * @class GenericIterator
 * @brief A generic Iterator class for kiwi resources
 */
template<typename ValueTypeT>
class GenericIterator
{
public:
	typedef ValueTypeT ValueType;

	inline bool next() { return (*this)++; }
	inline bool prev() { return (*this)--; }
	inline ValueType& get() {return *(*this);}
	
	virtual bool operator ++ () = 0;
	virtual bool operator -- () = 0;
	virtual ValueType& operator * () = 0;
	virtual bool operator == (const GenericIterator<ValueType>& it) = 0;
	
	inline bool operator != (const GenericIterator<ValueType>& it) {return !(*this == it); }
};

/**
 * @class GenericIterator
 * @brief A generic const Iterator class for kiwi resources
 */
template<typename ValueTypeT>
class GenericConstIterator
{
public:
	typedef ValueTypeT ValueType;

	inline bool next() { return (*this)++; }
	inline bool prev() { return (*this)--; }
	inline ValueType get() {return *(*this);}
	
	virtual bool operator ++ () = 0;
	virtual bool operator -- () = 0;
	virtual ValueType operator * () = 0;
	virtual bool operator == (const GenericIterator<ValueType>& it) = 0;
	
	inline bool operator != (const GenericIterator<ValueType>& it) {return !(*this == it); }
};



} //namespace image
} //namespace kiwi


#endif
