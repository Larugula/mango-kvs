//
// Created by alclol on 4/10/20.
//
#include <iostream>
#include "base_kvs.hpp"

int main(int argc, char** argv) {
   std::map<std::string, Lattice<std::tuple<VectorClock, Lattice<int, Max>>, CausalMerge>> initial_map;
   KVStore<std::string, Lattice<int, Max>> kvs(initial_map);
   std::string s1 = "Matthew";
   VectorClock vc1({{"x", Lattice(static_cast<unsigned>(2), Max{})},
                    {"y", Lattice(static_cast<unsigned>(4), Max{})}});
   std::tuple<VectorClock, Lattice<int, Max>> v1(vc1, Lattice(777, Max{}));
   kvs.put(s1, v1);
   std::cout << kvs.get(s1).reveal() << std::endl;
   return 0;
}