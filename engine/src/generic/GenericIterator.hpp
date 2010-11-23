//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#ifndef KIWI_GENERICITERATOR_HPP
#define KIWI_GENERICITERATOR_HPP


namespace kiwi
{
namespace generic
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

	inline bool next() { return ++(*this); }
	inline bool prev() { return --(*this); }
	inline ValueType& operator * () { return *_ptr; }
	inline ValueType& get() { return *_ptr; }
	inline ValueType* ptr() const { return _ptr; } 
	bool operator == (const GenericIterator<ValueType>& it)
		{ return _ptr == it.ptr; }
	inline bool operator != (const GenericIterator<ValueType>& it) {return !(*this == it); }

	// virtual
	virtual GenericIterator& operator ++ (int) = 0;
	virtual GenericIterator& operator -- (int) = 0;
	
protected:
	ValueType* _ptr;
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

	inline bool next() { return ++(*this); }
	inline bool prev() { return ++(*this); }
	inline ValueType operator * () { return *_ptr;}
	inline ValueType get() {return *_ptr;}
	inline const ValueType* const ptr() const { return _ptr; }
	
	inline bool operator == (const GenericConstIterator<ValueType>& it)
		{ return _ptr == it.ptr; }
	
	inline bool operator != (const GenericConstIterator<ValueType>& it) 
		{return !(*this == it); }


	virtual GenericConstIterator& operator ++ (int) = 0;
	virtual GenericConstIterator& operator -- (int) = 0;


protected:
	ValueType* _ptr;
	int a;
};



} //namespace 
} //namespace kiwi


#endif
