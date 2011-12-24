
#ifndef KIWI_CORE_DATATYPEMANAGER_HPP
#define KIWI_CORE_DATATYPEMANAGER_HPP

#include "kiwi/core/Data.hpp"




namespace kiwi{
namespace core{

/**
 * Manager for runtime data type info.
 */ 
class DataTypeManager
{
public:
    /**
     * Registers a data type into the manager.
     *
     * Should be invoked for every data type before they are used.
     */ 
    static const DataTypeInfo* RegisterDataType(string uniqueName, DataTypeInfo::Instanciator instanciator);

    /**
     * Returns the runtime type info for a given name.
     */ 
    static const DataTypeInfo* TypeOf(string name);

    /**
     * Instanciates a Data object correspônding to the name passed in parameter.
     *
     * The name must correspond to the one used when registering the data type.
     * Returns a nil pointer if the name is not registered in the manager. 
     */ 
    static Data* Create(string name);

};

const DataTypeInfo* KIWI_DTM_TypeOf(string name);

}//namespace
}//namespace

#endif
