#ifndef KIWI_CORE_NODELISTENER_HPP
#define KIWI_CORE_NODELISTENER_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{

class NodeListener
{
public:
	virtual void layoutChanged(int portType, portIndex_t index) = 0;
	~NodeListener() {}
};

}//namespace
}//namespace

#endif
