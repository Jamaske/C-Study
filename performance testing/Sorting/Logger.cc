#include "Logger.hh"
#include <cmath>
#include <algorithm>
#include <numeric>

Logger::Logger(const std::string& filePath, int datasetSize, bool verbose) : logFile(filePath), datasetSize(datasetSize), verbose(verbose) {
    if (!logFile) {
        throw std::runtime_error("Failed to open log file");
    }
    results = std::vector<double>(100);
    cnt = 0;
    algo = "None";
}



void Logger::set_algo(const std::string& algo) {
    summerize();
    this->algo = algo;
    cnt = 0;
    std::cout << "\n\n------" << algo << "-----\n";
    logFile << "\n---" << algo << "---\n";
}

void Logger::timestamp_ps(double time) {
    results[cnt] = time;
    if (verbose) {
        std::cout << "burst: " << cnt << " | clock: " << time << '\n';
        logFile << cnt << ", " << time << '\n';
    }
    ++cnt;
}

void Logger::summerize() {
    if (!cnt) return;
    double mean = std::accumulate(results.begin(), results.begin() + cnt, .0F) / cnt;
    std::transform(results.begin(), results.begin() + cnt, results.begin(), [mean](double time) {return (time - mean) * (time - mean);});
    double dispersion = std::sqrt(std::accumulate(results.begin(), results.begin() + cnt, .0F) / cnt);
    if (verbose) std::cout << algo << " - results\n";
    std::cout << "mean:  " << mean << " | dipsersion: " << dispersion << '\n';
    std::cout << "clk/item: " << mean / datasetSize << " | dips/mean: " << dispersion * 100 / mean << "%\n";
    logFile << '\n' << mean << ", " << dispersion << '\n' << mean / datasetSize << ", " << dispersion / mean << '\n';
}

Logger::~Logger() {
    summerize();
    logFile.close();
}
