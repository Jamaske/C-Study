#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Logger {
private:
    std::ofstream logFile;
    std::string algo;
    std::vector<double> results;
    int cnt;
    const int datasetSize;
    const bool verbose;

public:
    Logger(const std::string& filePath, int datasetSize, bool verbose = true);
    void set_algo(const std::string& algo);
    void timestamp_ps(double time);
    void summerize();
    ~Logger();
};