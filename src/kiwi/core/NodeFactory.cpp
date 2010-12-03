

#include "NodeFactory.hpp"



namespace kiwi
{
namespace core
{




kiwi::core::Node* NodeFactory::newNode(const  kiwi::string& uniqueId)
{
	
}

kiwi::core::Filter* NodeFactory::newFilter(const  kiwi::string& uniqueId)
{
	FilterMap::iterator it = _filters.find(uniqueId);
	if(it == _filters.end() ) return 0;
	Descriptor<Filter>* desc = it->second;
	return (desc->creator())();
}

kiwi::core::Container* NodeFactory::newContainer(const  kiwi::string& uniqueId)
{
	ContainerMap::iterator it = _containers.find(uniqueId);
	if(it == _containers.end() ) return 0;
	Descriptor<Container>* desc = it->second;
	return (desc->creator())();
}

int NodeFactory::exists(const  kiwi::string& uniqueId)
{
	if(_containers.find(uniqueId) != _containers.end() ) return CONTAINER;
	if( _filters.find(uniqueId) != _filters.end() ) return FILTER; 
	return FALSE;
}
	
void NodeFactory::registerNode(const kiwi::string& uniqueId, Descriptor<Container> nd)
{
	_containers[uniqueId] = new Descriptor<Container>(nd);
}

void NodeFactory::registerNode(const kiwi::string& uniqueId, Descriptor<Filter> nd)
{
	_filters[uniqueId] = new Descriptor<Filter>(nd);
}
	
void NodeFactory::unregister(const  kiwi::string& uniqueId)
{
	_containers.erase(_containers.find(uniqueId) );
	_filters.erase(_filters.find(uniqueId) );
}



}//namespace
}//namespace
