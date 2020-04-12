#include "arugula/include/lattice_core.hpp"
#include "arugula/include/merges/boolean_mrg.hpp"
#include "arugula/include/merges/maxmin_mrg.hpp"
#include "arugula/include/merges/setop_mrg.hpp"
#include "arugula/include/merges/map_mrg.hpp"
#include "arugula/include/merges/vector_clock_mrg.hpp"
#include "arugula/include/merges/causal_mrg.hpp"


// lmax

template<typename T>
Lattice<bool, Or> greater_than(Lattice<T, Max> l, T n) {
	T l_val = l.reveal();
	bool result = n > l_val;
	return Lattice(result, Or{});
};

template<typename T>
Lattice<bool, Or> greater_than_or_equal(Lattice<T, Max> l, T n) {
	T l_val = l.reveal();
	bool result = n >= l_val;
	return Lattice(result, Or{});
};

//lmin

template<typename T>
Lattice<bool, Or> less_than(Lattice<T, Min> l, T n) {
	T l_val = l.reveal();
	bool result = n < l_val;
	return Lattice(result, Or{});
};

template<typename T>
Lattice<bool, Or> less_than_or_equal(Lattice<T, Min> l, T n) {
	T l_val = l.reveal();
	bool result = n <= l_val;
	return Lattice(result, Or{});
};

//lset

template<typename T>
Lattice<T, Union> intersect(Lattice<std::set<T>, Union> l_left, Lattice<std::set<T>,Union> l_right) {
	std::set<T> l_left_val = l_left.reveal();
	std::set<T> l_right_val = l_right.reveal();
	
	set<T> res;
	for (auto elem : l_left_val) {
		if (l_right_val.count(elem))
			res.insert(elem);
	}
	return Lattice(res, Union{});
};

template<typename T>
Lattice<bool, Or> contains(Lattice<std::set<T>, Union> l_set, T v) {
	std::set<T> l_set_val = l_set.reveal();
	return Lattice(l_set_val.count(v), Or{});
};

//lmap

template<typename K, class T, class Func>
Lattice<std::map<K, Lattice<T, Func>>, MapUnion> intersect(Lattice<std::map<K, Lattice<T, Func>>, MapUnion> l_left, 
														   Lattice<std::map<K, Lattice<T, Func>>, MapUnion> l_right) {
	std::map<K, Lattice<T, Func>> l_left_val = l_left.reveal();
	std::map<K, Lattice<T, Func>> l_right_val = l_right.reveal();
	std::map<K, Lattice<T, Func>> result;
	for (const auto& [key, value] : l_left_val) {
		if (l_right_val.count(key) && value == l_right_val.at(key)) {
			res.insert(std::pair<K, Lattice<T, Func>>(key, value));
		}
	}
	return Lattice(res, MapUnion{});
};

template<typename K, class T, class Func>
Lattice<bool, Or> contains_key(Lattice<std::map<K, Lattice<T, Func>>, MapUnion> l, K key) {
	std::set<T> l_map_val = l_map.reveal();
	return Lattice(l_map_val.count(v), Or{});
}

template<typename K, class T, class Func>
Lattice<T, Func> At(Lattice<std::map<K, Lattice<T, Func>>, MapUnion> l_map, K key) {
	return l_map.reveal().at(key);
};

//idom : for kvs use only

template<class T, class Func>
Lattice<T, Func> get_value(Lattice < std::tuple<VectorClock, Lattice<T, Func>>, CausalMerge> idom) {
	return std::get<1>(idom.reveal());
};