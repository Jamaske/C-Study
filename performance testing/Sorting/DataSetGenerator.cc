#include "DataGenerator.hh"
#include <random>
#include <algorithm>

std::vector<std::vector<int>> DataSetGenerator::generate(int numSets, int setSize, unsigned seed) {
    std::vector<std::vector<int>> datasets(numSets, std::vector<int>(setSize));
    std::mt19937 rng(seed);
    for (auto& dataset : datasets) {
        std::generate(dataset.begin(), dataset.end(), rng);
    }
    return datasets;
}
