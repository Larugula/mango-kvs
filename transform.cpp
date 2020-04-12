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
	T left_val = l_left.reveal();
	T right_val = l_right.reveal();
	std::sort(left_val.begin(), left_val.end());
	std::sort(right_val.begin(), right_val.end());
	T res;
	std::set_intersection(left_val.begin(). left_val.end(), right_val.begin(), right_val.end(), res.begin());
};

template<typename K, class T, class Func>
Lattice<T, Func> At(Lattice<std::map<K, Lattice<T, Func>>, MapUnion> l, K key) {
	return l.reveal().at(key);
};

template<class T, class Func>
Lattice<T, Func> get_value(Lattice < std::tuple<VectorClock, Lattice<T, Func>>, CausalMerge> idom) {
	return std::get<1>(idom.reveal());
};