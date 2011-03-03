#ifndef KIWI_CORE_NODELISTENER_HPP
#define KIWI_CORE_NODELISTENER_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{


/**
 * @brief Mother class of any component that needs to be notfied of nodes state
 * changes.
 *
 * This class is intended mainly for integration with GUI components or any kind
 * of controler (for exemple to update the view when the node's layout changes).
 */ 
class NodeListener
{
public:
	/**
	 * @brief The method to override in order to react to changes in a Node.
	 */ 
	virtual void layoutChanged(int portType, portIndex_t index) = 0;
	~NodeListener() {}
};

}//namespace
}//namespace

#endif
