#pragma once
#include <vector>
struct DataSetGenerator {
    static std::vector<std::vector<int>> generate(int numSets, int setSize, unsigned seed = 0);
};