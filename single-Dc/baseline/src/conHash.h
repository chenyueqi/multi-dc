#ifndef __CONSISTENT_HASH_H__
#define __CONSISTENT_HASH_H__

#include <map>
#include <string>
#include <list>
#include <functional> 
#include <algorithm>
#include <boost/functional/hash.hpp>
#include <boost/format.hpp>
#include <boost/crc.hpp>
#include "city.h"

struct vnode{
    std::size_t id;
    std::size_t vid;

    vnode(std::size_t n, std::size_t v):id(n), vid(v) {}

    std::string to_str() const{
	return boost::str(boost::format("%1%-%2%") % id % vid);
    }
};


struct crc32
{
    typedef uint32_t result_type;

    uint32_t operator()(const vnode& node){
	boost::crc_32_type ret;
	std::string name = node.to_str();
	ret.process_bytes(name.c_str(), name.size());
	return ret.checksum();
    }
};

struct cityHash
{
    typedef uint32_t result_type;

    uint32_t operator()(const vnode& node){
	std::string name = node.to_str();
	return CityHash32(name.c_str(), name.size());
    }
};


template <typename T, typename Hash, typename Alloc = std::allocator<std::pair<const typename Hash::result_type,T > > >
class Conhash
{
    public:
	typedef typename Hash::result_type size_type;
	typedef std::map<size_type,T,std::less<size_type>,Alloc> map_type;
	typedef typename map_type::value_type value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename map_type::iterator iterator;
	typedef typename map_type::reverse_iterator reverse_iterator;
	typedef Alloc allocator_type;

    private:
	Hash hasher_;
	map_type nodes_;

    public:
	std::size_t size() const {return nodes_.size();}
	bool empty() const {return nodes_.empty();}

	std::pair<iterator,bool> insert(const T& node) {
	    size_type hash = hasher_(node);
	    return nodes_.insert(value_type(hash,node));
	}

	void erase(iterator it) {nodes_.erase(it);}


	std::size_t erase(const T& node) {
	    size_type hash = hasher_(node);
	    return nodes_.erase(hash);
	}

	iterator find(size_type hash) {
	    if(nodes_.empty()) 
		return nodes_.end();
	    iterator it = nodes_.lower_bound(hash);
	    if (it == nodes_.end())
		it = nodes_.begin();
	    return it;
	}

	iterator begin() { return nodes_.begin(); }
	iterator end() { return nodes_.end(); }
	reverse_iterator rbegin() { return nodes_.rbegin(); }
	reverse_iterator rend() { return nodes_.rend(); }
};

#endif
