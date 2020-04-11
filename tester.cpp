//
// Created by alclol on 4/10/20.
//
#include "base_kvs.hpp"

int main(int argc, char** argv) {
   KVStore<std::string, int> kvs;
   std::string s1 = "Matthew";
   VectorClock vc1({{"x", Lattice(static_cast<unsigned>(2), Max{})},
                    {"y", Lattice(static_cast<unsigned>(4), Max{})}});
   std::tuple<VectorClock, int> v1(vc1, 777);
   kvs.put(s1, v1);
   return 0;
}