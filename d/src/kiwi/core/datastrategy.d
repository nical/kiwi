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
        _accessFlags = flags_;
    }

    this( DataTypeInfo dataTypeInfo, DataAccessFlag flags_ )
    {
        _data = null;
        _dataType = dataTypeInfo;
        _accessFlags = flags_;
    }
    
    override
    {
        @property
        {
            int componentFlags() const { return DataStrategy.USER; }
            DataAccessFlag accessFlags() const { return _accessFlags; }
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
    this(InputPort port, DataTypeInfo dataTypeInfo)
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
            DataAccessFlag accessFlags() const
            {
                return _inputPort.accessFlags();
            }
            int componentFlags() const
            {
                return DataStrategy.USER;
            }
        }
    }
    
private:
    InputPort _inputPort;
    DataTypeInfo _dataType;
}

unittest
{

    auto c = new FromInputDataStrategy(null, null);

}
