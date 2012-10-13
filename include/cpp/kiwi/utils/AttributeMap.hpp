
#ifndef KIWI_UTILS_ATTRIBUTEMAP_HPP
#define KIWI_UTILS_ATTRIBUTEMAP_HPP

#include <map>
#include "kiwi/core/ID.hpp"

namespace kiwi {

template<typename T> struct NodeAttributeMap {
public:
    typedef std::map<NodeID, T> Map;

    T& operator[](NodeID id) {
        return _data[id];
    }
    const T& operator[](NodeID id) const {
        return _data[id];
    }
    size_t size() const {
        return _data.size();
    }

    typename Map::iterator begin() {
        return _data.begin();
    }
    typename Map::iterator end() {
        return _data.end();
    }
    typename Map::const_iterator begin() const {
        return _data.begin();
    }
    typename Map::const_iterator end() const {
        return _data.end();
    }
private:
    std::map<NodeID, T> _data;
};

template<typename T> struct NodeTypeInfoAttributeMap {
public:
    typedef std::map<NodeTypeID, T> Map;

    T& operator[](NodeTypeID id) {
        return _data[id];
    }
    const T& operator[](NodeTypeID id) const {
        return _data[id];
    }
    size_t size() const {
        return _data.size();
    }

    typename Map::iterator begin() {
        return _data.begin();
    }
    typename Map::iterator end() {
        return _data.end();
    }
    typename Map::const_iterator begin() const {
        return _data.begin();
    }
    typename Map::const_iterator end() const {
        return _data.end();
    }
private:
    std::map<NodeTypeID, T> _data;
};


} // namespace

#endif