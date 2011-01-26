#ifndef KIWI_UTILS_CONNECTOR_HPP
#define KIWI_UTILS_CONNECTOR_HPP

#include <list>
#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace utils{

template<class ThisType, class LinkType>
class AbstractConnector
{
public:
	typedef AbstractConnector<LinkType,ThisType> AbstractConnectorType;
	static const int ALL = 0;
	
	virtual kiwi::uint32_t nbConnections() const = 0;
	virtual bool canConnect() const = 0;

	virtual LinkType* connectedInstance(kiwi::uint32_t index = 0) const = 0;

	void connect( AbstractConnectorType* toConnect ){
		if( toConnect == 0 ) return;
		if( canConnect() && toConnect->canConnect() ){
			_connect_impl( toConnect );
			toConnect->_connect_impl( this );
		}
	}
	virtual void disconnect( AbstractConnectorType* toDisconnect = ALL ) = 0;

	virtual void _disconnect_impl( AbstractConnectorType* toDisconnect) = 0;
	virtual void _connect_impl( AbstractConnectorType* toConnect ) = 0;	

	

protected:
	
};

/*
 * The following files include different implementations of connectors,
 * in function of the MaxConnections template parameters.
 */


}//namespace
}//namespace


// default implementation (a std list contains the links) 
#include "kiwi/utils/Connector_default.ih"
// if only one connection allowed, no need for a list
#include "kiwi/utils/Connector_mono.ih"
// not implemented yet...
#include "kiwi/utils/Connector_any.ih"

#endif
