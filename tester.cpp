//
// Created by alclol on 4/10/20.
//
#include <iostream>
#include "base_kvs.hpp"

int main(int argc, char** argv) {
   std::map<std::string, Lattice<std::tuple<VectorClock, Lattice<int, Max>>, CausalMerge>> initial_map;
   KVStore<std::string, int, Max> kvs(initial_map);
   std::string s1 = "Matthew";
   VectorClock vc1({{"x", Lattice(static_cast<unsigned>(2), Max{})}});
   VectorClock vc2({{"x", Lattice(static_cast<unsigned>(2), Max{})},
                    {"y", Lattice(static_cast<unsigned>(3), Max{})}});
   std::tuple<VectorClock, Lattice<int, Max>> v1(vc1, Lattice(777, Max{}));
   std::tuple<VectorClock, Lattice<int, Max>> v2(vc2, Lattice(222, Max{}));
   kvs.put(s1, v1);
   kvs.put(s1, v2);
   std::cout << kvs.get(s1).reveal() << std::endl;
   return 0;
}