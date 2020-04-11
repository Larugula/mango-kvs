#include "base_kvs.hpp"

int main() {
    VectorClock vc1({{"x", Lattice(static_cast<unsigned>(2), Max{})},
                     {"y", Lattice(static_cast<unsigned>(4), Max{})}});
    VectorClock vc2({{"x", Lattice(static_cast<unsigned>(3), Max{})},
                     {"y", Lattice(static_cast<unsigned>(5), Max{})}});
    VectorClock vc3({{"x", Lattice(static_cast<unsigned>(1), Max{})},
                     {"y", Lattice(static_cast<unsigned>(6), Max{})}});
    Value<int> var1(vc1, 1);
    Value<int> var2(vc1, 2);
    Value<int> var3(vc1, 3);
    std::unordered_map<int, Lattice<Value<int>, CausalMerge>> map;

    KVStore<int, int> db(map);
    int k1 = 1;
    int k2 = 2;
    int k3 = 3;
    db.put(k1, var1);

}
