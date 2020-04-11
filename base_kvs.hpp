#include "arugula/include/lattice_core.hpp"
#include "arugula/include/merges/map_mrg.hpp"
#include "arugula/include/merges/vector_clock_mrg.hpp"
#include "arugula/include/merges/causal_mrg.hpp"
#include "arugula/include/merges/tuple_mrg.hpp"

template <typename K, typename V>
class KVStore {
protected:
  Lattice<std::map<K, Lattice<std::tuple<VectorClock, V>, CausalMerge>>, MapUnion> store;

public:
  KVStore<K, V>() {
      std::map<K, Lattice<std::tuple<VectorClock, V>, CausalMerge>> initial_map;
      store = Lattice(initial_map, MapUnion{});
  }
  KVStore<K, V>(std::map<K, Lattice<std::tuple<VectorClock, V>, CausalMerge>> &other) : store(other) { }

  V get(const K &k) {
    std::map<K, Lattice<std::tuple<VectorClock, V>, CausalMerge>> store_map = store.reveal();
    std::tuple<VectorClock, V> value_tuple = store_map.at(k).reveal();
    return std::get<1>(value_tuple);
  }

  void put(const K &k, std::tuple<VectorClock, V> &v) {
    std::map<K, Lattice<std::tuple<VectorClock, V>, CausalMerge>> store_map = store.reveal();
    if (store_map.find(k) != store_map.end())
        store_map.at(k).merge(v);
    else {
        std::map<K, Lattice<std::tuple<VectorClock, V>, CausalMerge>> new_map = { { k, Lattice(v, CausalMerge{}) } };
        store.merge(new_map);
    }
  }

  unsigned size(const K &k) { return store.at(k).size().reveal(); }
  void remove(const K &k) { store.remove(k); }
};

