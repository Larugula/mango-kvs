#include "arugula/include/lattice_core.hpp"
#include "arugula/include/merges/boolean_mrg.hpp"
#include "arugula/include/merges/maxmin_mrg.hpp"
#include "arugula/include/merges/setop_mrg.hpp"

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
};