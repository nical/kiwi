#ifndef KIWI_ARITHMETIC_ADDFILTER_HPP
#define KIWI_ARITHMETIC_ADDFILTER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/generic/NumberContainer.hpp"
#include "kiwi/utils/types.hpp"
#include "kiwi/core/StaticNode.hpp"



namespace kiwi{
namespace arithmetic{


#define KIWI_ADDFILTER_TYPE kiwi::float_t

// ---------------------------------------------------------------------- Layout
typedef kiwi::core::StaticNodeLayout<
  ReaderListMacro<
    kiwi::core::StaticReaderPort<generic::NumberContainer<kiwi::float_t> >,
    kiwi::core::StaticReaderPort<generic::NumberContainer<kiwi::float_t> > >,
  WriterListMacro<
    kiwi::core::StaticWriterPort<generic::NumberContainer<kiwi::float_t> > >,
  DataListMacro<
    kiwi::core::StaticDataPort< generic::NumberContainer<kiwi::float_t> > >
> addFilterLayout;
// -----------------------------------------------------------------------------


class AddFilter : public kiwi::core::StaticNode<addFilterLayout>
{
public:
	AddFilter(){
		_result = new kiwi::generic::NumberContainer<KIWI_ADDFILTER_TYPE>();
	}

	void process(){
		ScopedBlockMacro("AddFilter::process()" );
		if( _result ){
			
			typedef kiwi::generic::NumberContainerInterface<KIWI_ADDFILTER_TYPE> NumberContainer_T;

    	
			NumberContainer_T* ca = staticReaderPort<0>().getContainer();
			//	= readerPort(0).connectedPort()
      //    ->safeDownCastContainer<NumberContainer_T>();

			NumberContainer_T* cb = staticReaderPort<0>().getContainer();
			//	= readerPort(1).connectedPort()
			//		->safeDownCastContainer<NumberContainer_T>();

			if(!ca){
				Debug::error()
					<< "AddFilter::process(): error \n"
					<<"could not get the frist input container"  << endl();
				return;
			}
			if(!cb){
				Debug::error()
					<< "AddFilter::process(): error \n"
					<<"could not get the second input container" << endl();
				return;
			}


			int A = ca->getValue();

			int B = cb->getValue();

			_result->setValue( A + B );

		}
	}

	template<typename TypeR>
	void processTemplate()
	{

	}

	kiwi::utils::Tags readerInputTags(kiwi::portIndex_t index) const{
		Debug::print() << "AddFilter::Tags" << endl();
		return kiwi::utils::Tags("#float");// TODO
	}

	void layoutChanged(){
		if( readerPort(0).isConnected()
		&& readerPort(1).isConnected() ){
			if( _result == 0 ){
				_result = new kiwi::generic::NumberContainer<KIWI_ADDFILTER_TYPE>( 0 );
				setDataPortContainer( dataPort(0), _result );
//				setPortEnabled( dataPort(0), false );
			}
		}else{
			if( _result != 0){
				delete _result;
				_result = 0;
				setDataPortContainer( dataPort(0), 0 );
			}
		}
	}


protected:
	kiwi::generic::NumberContainerInterface<KIWI_ADDFILTER_TYPE>* _result;
	template<typename T1,typename T2> void process2();
};


}//namespace
}//namespace


#endif
