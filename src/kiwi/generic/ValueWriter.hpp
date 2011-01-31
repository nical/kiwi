
#pragma once

#ifndef KIWI_GENERIC_VALUEREADER_HPP
#define KIWI_GENERIC_VALUEREADER_HPP



template<typename TValueType>
class ValueWriter : public core::Writer
{
public:
	typedef TValueType ValueType;
	// -----------------------------------------------------------------
	ValueWriter(const core::WriterInputPort& port)
	{
		_resource = dynamic_cast<ValueContainerInterface<TValueType>* >(
			port.connectedOutput()->data()
		);
		DEBUG_ONLY(
			if(!_resource)
			{
				Debug::error() << "ValueWriter<"
					<< types::str<ValueType>()
					<< ">::Constructor : "
					<< "enable to determine the Container type"
					<< endl();
			}
		)//DEBUG_ONLY
		//_port = port.connectedOutput()->subPort()->index();
	}


	virtual ValueType& get() const {return _container->value(_port);}
	virtual void set(ValueType val) {_resource->value(_port) = val; }
private:
	ValueContainerInterface<ValueType>* _container;
};

#endif
