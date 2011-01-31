
#pragma once

#ifndef KIWI_GENERIC_VALUEREADER_HPP
#define KIWI_GENERIC_VALUEREADER_HPP

// ----------------------------------------------------- Reader / Writer
template<typename TValueType>
class ValueReader : public core::Reader
{
public:
	typedef TValueType ValueType;
	// -----------------------------------------------------------------
	ValueReader(const core::ReaderInputPort& port)
	{
		assert( port.connectedOutput()->data() );

		_container = dynamic_cast<ValueContainerInterface<TValueType>* >(
			port.data()
		);
		if(!_container)
		{
			Debug::error() << "ValueReader<"
				<< types::str<ValueType>()
				<< ">::Constructor : "
				<< "enable to determine the Container type"
				<< endl();
		}
	}

	ValueType value() const {return _container->value();}

private:
	ValueContainerInterface<ValueType>* _container;
};


#endif
