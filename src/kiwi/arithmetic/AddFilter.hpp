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
    associateWriterToDataPort( staticWriterPort<0>(), staticDataPort<0>() );
	}

  void process(){
		ScopedBlockMacro("AddFilter::process()" );
  
    
    typedef kiwi::generic::NumberContainerInterface<KIWI_ADDFILTER_TYPE> NumberContainer_T;

    
    NumberContainer_T* ca = staticReaderPort<0>().getContainer();			
    NumberContainer_T* cb = staticReaderPort<1>().getContainer();
    NumberContainer_T* result = staticWriterPort<0>().getContainer();

    
    if(!ca){
      Debug::error()
        << "AddFilter::process(): error \n"
        <<"could not get the frist input container"  << endl();
    }
    if(!cb){
      Debug::error()
        << "AddFilter::process(): error \n"
        <<"could not get the second input container" << endl();
    }
    if(!result){
      Debug::error()
        << "AddFilter::process(): error \n"
        <<"could not get the writer port's container" << endl();
      return;
    }

    int A = ca ? ca->getValue() : 0;
    int B = cb ? cb->getValue() : 0;

    result->setValue( A + B );
	}

	template<typename TypeR>
	void processTemplate()
	{

	}

	kiwi::utils::Tags readerInputTags(kiwi::portIndex_t index) const{
		Debug::print() << "AddFilter::Tags" << endl();
		return kiwi::utils::Tags("#float");// TODO
	}

protected:
	//kiwi::generic::NumberContainerInterface<KIWI_ADDFILTER_TYPE>* _result;
	template<typename T1,typename T2> void process2();
};


}//namespace
}//namespace


#endif
