#ifndef KIWI_UTILS_CONNECTOR_HPP
#define KIWI_UTILS_CONNECTOR_HPP

#include <list>
#include "kiwi/core/Commons.hpp"

template<class ThisType, class LinkType>
class AbstractConnector
{
public:
	typedef AbstractConnector<LinkType,ThisType> AbstractConnectorType;
	virtual kiwi::uint32_t nbConnections() const = 0;
	virtual bool canConnect() const = 0;
	virtual void connect2( AbstractConnector<LinkType,ThisType>* toConnect ) = 0;
	virtual void disconnect2( AbstractConnector<LinkType,ThisType>* toDisconnect) = 0;
	virtual LinkType* connectedInstance(kiwi::uint16_t index = 0) const = 0;

	void connect( AbstractConnectorType* toConnect ){
		if( toConnect == 0 ) return;
		if( canConnect() && toConnect->canConnect() ){
			connect2( toConnect );
			toConnect->connect2( this );
		}
	}
};

/*
 * The following files include different implementations of connectors,
 * in function of the MaxConnections template parameters.
 */

// default implementation (a std list contains the links) 
#include "kiwi/utils/Connector_default.ih"
// if only one connection allowed, no need for a list
#include "kiwi/utils/Connector_mono.ih"
// not implemented yet...
#include "kiwi/utils/Connector_any.ih"

#endif
