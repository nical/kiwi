
#ifndef KIWI_CORE_DATATYPEMANAGER_HPP
#define KIWI_CORE_DATATYPEMANAGER_HPP

#include "kiwi/core/Data.hpp"
#include "kiwi/core/DataTypeId.hpp"




namespace kiwi{
namespace core{

class DataTypeInfo;
class DataTypeContainer;

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

    DataTypeManager();
    ~DataTypeManager();

    /**
     * Registers a data type into the manager.
     *
     * Should be invoked for every data type before they are used.
     */ 
    const DataTypeInfo* registerDataType(const string& uniqueName, DataTypeInfo::Instanciator instanciator);

    /**
     * Returns the runtime type info for a given name.
     */ 
    const DataTypeInfo* typeOf(const string& name);

    /**
     * Instanciates a Data object correspônding to the name passed in parameter.
     *
     * The name must correspond to the one used when registering the data type.
     * Returns a nil pointer if the name is not registered in the manager. 
     */ 
    Data* instanciate(const string& name);

private:

    DataTypeContainer* _types;
};


const DataTypeInfo* Kiwi_DTM_TypeOf(string name);


}//namespace
}//namespace

#endif
