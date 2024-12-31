#pragma once
#include <vector>
#include <functional>
#include "Logger.hh"

class BenchmarkExecutor {
private:
    int measurement;
    int burst;
    int warmup;

public:
    BenchmarkExecutor(int measurement = 100, int burst = 100, int warmup = 5);
    void run(std::function<void(std::vector<int>&)> sort, const std::vector<std::vector<int>>& datasets, Logger& log);
};