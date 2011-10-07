
#include "kiwi/core/Commons.hpp"


namespace kiwi{
namespace core{



class DataTypeInfo
{
public:
	typedef std::vector<DataTypeInfo*> SubDataArray;
	typedef Data* (*Instanciator)();

	DataTypeInfo(string dataName, SubDataArray subdata, Instanciator instanciator)
	: _name(dataName), _subData(subdata), _newFunction(instanciator)
	{

	}

	string name() const
	{
		return _name;
	}
	const SubDataArray& subData() const
	{
		return _subData;
	}

	bool isComposite()
	{
		return _subData.size() != 0;
	}

	Data* newInstance() const
	{
		return (*_newFunction)();
	}
private:
	string _name;
	SubDataArray _subData;
	Instanciator _newFunction;
};

class Data
{
	enum{ READ = 1, WRITE = 2, READ_WRITE = READ | WRITE
		, DATA = 4, SIGNAL = 8, SEMANTIC = 16 };
	virtual DataTypeInfo* type() = 0;
};


}//namespace
}//namespace
