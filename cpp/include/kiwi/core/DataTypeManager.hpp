
#ifndef KIWI_CORE_DATATYPEMANAGER_HPP
#define KIWI_CORE_DATATYPEMANAGER_HPP

#include "kiwi/core/Data.hpp"
#include "kiwi/core/DataTypeId.hpp"




namespace kiwi{
namespace core{


class DataTypeInfo;
class DataHeader;
struct DataTypeExtension
{
    
};


/**
 * Manager for runtime data type info.
 */ 
class DataTypeManager
{
public:
    typedef uint32 Status;
    typedef void*(Instanciator)(void);
    typedef struct{ Instanciator instanciator; DataTypeExtension extension; } DTypeInfo;

    DataHeader* createInstance( DataTypeId datatype );
    Status registerDataType( DataTypeId datatype, Instanciator instanciator, DataTypeExtension* extension = 0 );
    bool exists( DataTypeId datatype );
    DataTypeExtension* extension( DataTypeId datatype );


// ------------------------------------------------------------------ Transition
// DataTypeInfo will be replaced by DataTypeId and each type manager will have
// it's own data typê base

    const DataTypeInfo* registerDataType(const string& uniqueName, DataTypeInfo::Instanciator instanciator)
    {
        return DataTypeManager::_RegisterDataType(uniqueName,instanciator);
    }

    const DataTypeInfo* typeOf( const string& name)
    {
        return DataTypeManager::_TypeOf(name);
    }

    Data* instanciate( const string& name)
    {
        return DataTypeManager::_Create(name);
    }


protected:
// ------------------------------------------------------------------ Deprecated

    /**
     * Registers a data type into the manager.
     *
     * Should be invoked for every data type before they are used.
     */ 
    static const DataTypeInfo* _RegisterDataType(string uniqueName, DataTypeInfo::Instanciator instanciator);

    /**
     * Returns the runtime type info for a given name.
     */ 
    static const DataTypeInfo* _TypeOf(string name);

    /**
     * Instanciates a Data object correspônding to the name passed in parameter.
     *
     * The name must correspond to the one used when registering the data type.
     * Returns a nil pointer if the name is not registered in the manager. 
     */ 
    static Data* _Create(string name);

};


const DataTypeInfo* Kiwi_DTM_TypeOf(string name);


}//namespace
}//namespace

#endif
