
#pragma once
#ifndef KIWI_CORE_STATICPORTS_HPP
#define KIWI_CORE_STATICPORTS_HPP

//forward declarations
namespace kiwi{
namespace core{
  template<class TContainerType, int TFlag> class StaticDataPort;
  template<class TContainerType, class ConnectionPolicy> class StaticWriterPort;
  template<class TContainerType, class ConnectionPolicy> class StaticReaderPort;
}//namespace
}//namespace
#include "kiwi/core/StaticReaderPort_decl.hpp"
#include "kiwi/core/StaticWriterPort_decl.hpp"
#include "kiwi/core/StaticDataPort_decl.hpp"

#define KIWI_DO_INCLUDE_STATICWRITERPORT_DEF_HPP
#include "kiwi/core/StaticWriterPort_def.hpp"
#undef KIWI_DO_INCLUDE_STATICWRITERPORT_DEF_HPP

#define KIWI_DO_INCLUDE_STATICREADERPORT_DEF_HPP
#include "kiwi/core/StaticReaderPort_def.hpp"
#undef KIWI_DO_INCLUDE_STATICREADERPORT_DEF_HPP

#define KIWI_DO_INCLUDE_STATICDATAPORT_DEF_HPP
#include "kiwi/core/StaticDataPort_def.hpp"
#undef KIWI_DO_INCLUDE_STATICDATAPORT_DEF_HPP

#endif
