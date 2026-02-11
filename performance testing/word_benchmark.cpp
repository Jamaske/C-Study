#include <benchmark/benchmark.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

// Global word list and metrics
static std::vector<std::string> g_words;
static size_t g_total_chars = 0;

// Function to read and parse words.txt
bool read_words_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        std::string word;
        while (line_stream >> word) {
            g_words.push_back(word);
            g_total_chars += word.size();
        }
    }

    if (g_words.empty()) {
        std::cerr << "Error: No words found in file.\n";
        return false;
    }

    std::cout << "Loaded " << g_words.size() << " words, "
              << g_total_chars << " total characters.\n";
    return true;
}

// ================= BENCHMARK DEFINITIONS =================

// 1. BASELINE: Copy words only (no spaces)
static void BM_WordCopyOnly(benchmark::State& state) {
    // Calculate exact buffer size needed
    size_t buffer_size = g_total_chars;
    alignas(64) std::vector<char> buffer(buffer_size);

    for (auto _ : state) {
        char* ptr = buffer.data();
        for (const auto& word : g_words) {
            // Use memcpy for maximum speed (compiler will optimize)
            std::memcpy(ptr, word.data(), word.size());
            ptr += word.size();
            // NO SPACE written
        }
        // Prevent compiler from optimizing away the work
        benchmark::DoNotOptimize(buffer.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_WordCopyOnly);

// 2. STRATEGY A: Explicit space writes in loop
static void BM_ExplicitSpaces(benchmark::State& state) {
    // Buffer size: total chars + spaces between words
    size_t buffer_size = g_total_chars + g_words.size() - 1;
    alignas(64) std::vector<char> buffer(buffer_size);

    for (auto _ : state) {
        char* ptr = buffer.data();
        for (size_t i = 0; i < g_words.size(); ++i) {
            std::memcpy(ptr, g_words[i].data(), g_words[i].size());
            ptr += g_words[i].size();
            *ptr++ = ' ';  // Single-byte space write
        }
        *ptr = '\n';
        benchmark::DoNotOptimize(buffer.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_ExplicitSpaces);

// 3. STRATEGY B: memset spaces first, then copy words
static void BM_MemsetSpaces(benchmark::State& state) {
    size_t buffer_size = g_total_chars + g_words.size() - 1;
    alignas(64) std::vector<char> buffer(buffer_size);

    for (auto _ : state) {
        char* ptr = buffer.data();
        // Step 1: Fill entire buffer with spaces
        std::memset(ptr, ' ', buffer_size);

        // Step 2: Copy words, overwriting spaces
        for (const auto& word : g_words) {
            std::memcpy(ptr, word.data(), word.size());
            ptr += word.size() + 1;  // +1 to skip pre-filled space
        }
        benchmark::DoNotOptimize(buffer.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_MemsetSpaces);

// ================= MAIN & SETUP =================
int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);

    if (!read_words_from_file("words.txt")) return 1;

    BENCHMARK(BM_WordCopyOnly)->Iterations(300000);
    BENCHMARK(BM_ExplicitSpaces)->Iterations(300000);
    BENCHMARK(BM_MemsetSpaces)->Iterations(300000);

    ::benchmark::RunSpecifiedBenchmarks();
    char x;
    std::cin >> x;
    return 0;
}