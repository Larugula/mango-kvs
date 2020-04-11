#include "arugula/include/lattice_core.hpp"
#include "arugula/include/merges/boolean_mrg.hpp"
#include "arugula/include/merges/maxmin_mrg.hpp"
#include "arugula/include/merges/setop_mrg.hpp"
#include "arugula/include/merges/map_mrg.hpp"
#include "arugula/include/merges/vector_clock_mrg.hpp"
#include "arugula/include/merges/causal_mrg.hpp"

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

template<typename T>
Lattice<T, Union> intersect(Lattice<T, Union> l_left, Lattice<T, Union> l_right) {
	std::set<T> l_left_val = l_left.reveal();
	std::set<T> l_right_val = l_right.reveal();
	std::sort(l_left_val.begin(), l_left_val.end());
	std::sort(l_right_val.begin(), l_right_val.end());
	//TODO
};

template<typename K, class T, class Func>
Lattice<T, Func> At(Lattice<std::map<K, Lattice<T, Func>>, MapUnion> l, K key) {
	return l.reveal().at(key);
};

template<class T, class Func>
Lattice<T, Func> get_value(Lattice < std::tuple<VectorClock, Lattice<T, Func>>, CausalMerge> idom) {
	return std::get<1>(idom.reveal());
};