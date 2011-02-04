#ifndef KIWI_ARITHMETIC_ADDFILTER_HPP
#define KIWI_ARITHMETIC_ADDFILTER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/generic/NumberContainer.hpp"

namespace kiwi{
namespace arithmetic{

class AddFilter : public kiwi::core::Filter
{
public:
	AddFilter(){
		_result = new kiwi::generic::NumberContainer<int>(12);
		addReaderInputPort(); // A
		addReaderInputPort(); // B
		addReaderOutputPort( _result );
	}

	void process(){
		ScopedBlockMacro( __scrop,"AddFilter::process()" );
		if( _result ){
			Debug::print() << "get data A\n";
			kiwi::generic::NumberContainerInterface<int>* ca
				= dynamic_cast<kiwi::generic::NumberContainerInterface<int>*>(readerInputPort(0).connectedOutput()->data() );
			Debug::print() << "get data A\n";
			kiwi::generic::NumberContainerInterface<int>* cb
				= dynamic_cast<kiwi::generic::NumberContainerInterface<int>*>(readerInputPort(1).connectedOutput()->data() );
			Debug::print() << "get value A\n";
			int A = 0;
			if(ca) A = ca->getValue();
			Debug::print() << "get value A\n";
			int B = 0;
			if(cb) B = cb->getValue();

			_result->setValue( A + B );

		}
	}

	kiwi::Tags readerInputTags(kiwi::portIndex_t index) const{
		return kiwi::Tags("#number#any");// TODO
	}

	void layoutChanged(){
		if( readerInputPort(0).isConnected()
		&& readerInputPort(1).isConnected() ){
			if( _result == 0 ){
				_result = new kiwi::generic::NumberContainer<int>( 0 );
				setPortContainer( readerOutputPort(0), _result );
				setPortEnabled( readerOutputPort(0), false );
			}
		}else{
			if( _result != 0){
				delete _result;
				_result = 0;
				setPortEnabled( readerOutputPort(0), false );
			}
		}
	}


protected:
	kiwi::generic::NumberContainerInterface<int>* _result;
	template<typename T1,typename T2> void process2();
};


}//namespace
}//namespace


#endif
