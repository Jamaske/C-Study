#include "BenchmarkExecutor.hh"
#include <intrin.h>
#include <cstdint>



BenchmarkExecutor::BenchmarkExecutor(int measurement, int burst, int warmup) : measurement(measurement), burst(burst), warmup(warmup) {}

void BenchmarkExecutor::run(std::function<void(std::vector<int>&)> sort, const std::vector<std::vector<int>>& datasets, Logger& log) {
    std::vector<std::vector<int>> copy(datasets.size());

    for (int j = 0; j < measurement; ++j) {
        std::copy(datasets.begin(), datasets.end(), copy.begin());

        // Warmup phase
        int i = 0;
        for (; i < warmup; ++i) {
            sort(copy[i]);
        }

        // Measure burst
        uint64_t start = __rdtsc();
        for (; i < warmup + burst; ++i) {
            sort(copy[i]);
        }
        uint64_t end = __rdtsc();

        uint64_t elapsed = end - start;
        log.timestamp_ps(elapsed / burst);
    }
}
