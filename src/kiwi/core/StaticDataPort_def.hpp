
#ifdef KIWI_DO_INCLUDE_STATICDATAPORT_DEF_HPP
#ifndef KIWI_CORE_STATICDATAPORT_DEF_HPP
#define KIWI_CORE_STATICDATAPORT_DEF_HPP

namespace kiwi{
namespace core{


template<class TContainerType, int TFlag>
template<typename T1, typename policy>
bool StaticDataPort<TContainerType, TFlag>::operator >> ( StaticReaderPort<T1, policy>& readerPort ){
ScopedBlockMacro("StaticDataPort::SafeConnect" )
  if(isEnabled() && readerPort.isEnabled() ){
    connectWithoutChecking( &readerPort );
    return true;
  }else return false;
}

template<class TContainerType, int TFlag>
template<typename T1, typename policy>
bool StaticDataPort<TContainerType, TFlag>::operator >> ( StaticWriterPort<T1,policy>& writerPort ){
ScopedBlockMacro("StaticDataPort::SafeConnect" )
  if(isEnabled() && writerPort.isEnabled() ){
    connectWithoutChecking( &writerPort );
    return true;
  }else return false;
}



}//namespace
}//namespace


#endif
#endif
