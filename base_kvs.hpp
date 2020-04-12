#include "arugula/include/lattice_core.hpp"
#include "arugula/include/merges/map_mrg.hpp"
#include "arugula/include/merges/vector_clock_mrg.hpp"
#include "arugula/include/merges/causal_mrg.hpp"
#include "arugula/include/merges/tuple_mrg.hpp"
#include "transform.cpp"

template <typename K, class T, class Func>
class KVStore {
protected:
  Lattice<std::map<K, Lattice<std::tuple<VectorClock, Lattice<T, Func>>, CausalMerge>>, MapUnion> store;

public:
  KVStore<K, T, Func>() : store(Lattice(std::map<K, Lattice<std::tuple<VectorClock, Lattice<T, Func>>, CausalMerge>>(), MapUnion{})) { }
  KVStore<K, T, Func>(std::map<K, Lattice<std::tuple<VectorClock, Lattice<T, Func>>, CausalMerge>> &other) : store(other) { }

  Lattice<T, Func> get(const K &k) {
    //return get_value((At(store, k)));
      return store.At<K, Lattice<std::tuple<VectorClock, Lattice<T, Func>>, CausalMerge>>(k).get_value<VectorClock, Lattice<T, Func>>();
  }

  void put(const K &k, std::tuple<VectorClock, Lattice<T, Func>> &v) {
    std::map<K, Lattice<std::tuple<VectorClock, Lattice<T, Func>>, CausalMerge>> new_map = { { k, Lattice(v, CausalMerge{}) } };
    store.merge(new_map);
  }

  unsigned size(const K &k) { return store.at(k).size().reveal(); }
  void remove(const K &k) { store.remove(k); }
};

