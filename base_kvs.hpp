#include "arugula/include/lattice_core.hpp"
#include "arugula/include/merges/map_mrg.hpp"
#include "arugula/include/merges/vector_clock_mrg.hpp"
#include "arugula/include/merges/causal_mrg.hpp"

template<typename T>
struct Value {
    VectorClock vc;
    T value;
};

template <typename K, typename V> 
class KVStore {
protected:
  std::map<K, Lattice<Value<V>, CausalMerge> > store;

public:
  KVStore<K, V>() {}
  KVStore<K, V>(std::map<K, Lattice<Value<V>, CausalMerge>> &other) : store(other) { }

  Value<V> get(const K &k) {
    return store.at(k).reveal();
  }

  void put(const K &k, Value<V> &v) {
    if (store.find(k) != store.end())
        store.at(k).merge(v);
    else 
        store[k] = v;
  }

  unsigned size(const K &k) { return store.at(k).size().reveal(); }
  void remove(const K &k) { store.remove(k); }
};

