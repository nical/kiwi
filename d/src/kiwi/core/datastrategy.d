module kiwi.core.datastrategy;

import kiwi.core.port;
import kiwi.core.data;
import kiwi.core.commons;






class UserAllocatedDataStrategy : DataStrategy
{
    this( Data data_, DataAccessFlag flags_ )
    {
        _data = data_;
        _dataType = data_.type;
    }

    this( DataTypeInfo dataTypeInfo, DataAccessFlag flags_ )
    {
        _data = null;
        _dataType = dataTypeInfo;
    }
    
    override
    {
        @property
        {
            int componentFlags(){ return DataStrategy.USER; }
            DataAccessFlag accessFlags(){ return _accessFlags; }
            Data data(){ return _data; }
            DataTypeInfo dataType(){ return _dataType; }
            
        }
        
    }
private:
    Data _data;
    DataTypeInfo _dataType;
    DataAccessFlag _accessFlags;
}



class SubDataStrategy : DataStrategy
{
    this( Data data_, DataAccessFlag flags_ )
    {
        _data = data_;
        _dataType = data_.type;
    }

    this( DataTypeInfo dataTypeInfo, DataAccessFlag flags_ )
    {
        _data = null;
        _dataType = dataTypeInfo;
    }
    
    override
    {
        @property
        {
            int componentFlags(){ return DataStrategy.USER; }
            DataAccessFlag accessFlags(){ return _accessFlags; }
            Data data(){ return _data; }
            DataTypeInfo dataType(){ return _dataType; }
            
        }
    }
private:
    Data _data;
    DataTypeInfo _dataType;
    DataAccessFlag _accessFlags;
}

class FromInputDataStrategy : DataStrategy
{
    this(InPort port, DataTypeInfo dataTypeInfo)
    {
        _inputPort = port;
        _dataType = dataTypeInfo;
    }

    override
    {
        @property
        {
            Data data()
            {
                if(_inputPort !is null )
                {
                    return _inputPort.data;
                }
                return null;
            }            
            DataTypeInfo dataType()
            {
                return _dataType;
            }
            DataAccessFlag accessFlags()
            {
                return _inputPort.accessFlags();
            }
            int componentFlags()
            {
                return DataStrategy.USER;
            }
        }
    }
    
private:
    InPort _inputPort;
    DataTypeInfo _dataType;
}

unittest
{

    auto c = new FromInputDataStrategy(null, null);

}
