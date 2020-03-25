#ifndef KVS_INCLUDE_KVS_COMMON_HPP_
#define KVS_INCLUDE_KVS_COMMON_HPP_

#include <unordered_map>
// TODO: include

template<typename V>
struct Value {
    VectorClock vc;
    V value;
};

template <typename K, typename V> 
class KVStore {
protected:
  std::unordered_map<K, Lattice<struct Value, CasualMerge{}> > store;

public:
  KVStore<K, V>() {}
  KVStore<K, V>(std::unordered_map<K, Lattice<struct Value, CasualMerge{}> &other) : store(other) { }

  struct Value get(const K &k) {
    return store.at(k).reveal();
  }

  void put(const K &k, struct Value &v) { 
    if (store.find(k) != store.end())
        store.at(k).merge(v);
    else 
        store[k] = v;
  }

  unsigned size(const K &k) { return store.at(k).size().reveal(); }
  void remove(const K &k) { store.remove(k); }
};

