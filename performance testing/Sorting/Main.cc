#include <vector>
#include <algorithm>
#include <string>
#include <cstdint>

#include "DataGenerator.hh"
#include "Logger.hh"
#include "BenchmarkExecutor.hh"

// Example heap sort implementation
auto quickSort = [](std::vector<int>& data) { std::sort(data.begin(), data.end()); };

void heapSort(std::vector<int>& data) {
    std::make_heap(data.begin(), data.end());
    std::sort_heap(data.begin(), data.end());
}


void linear_reference(std::vector<int>& data) {
    uint64_t len = data.size();
    int mask = 0;
    for (uint64_t i = 0; i < len; ++i) {
        mask ^= data[i];
    }
    data[0] = mask;
}


void square_reference(std::vector<int>& data) {
    uint64_t len = data.size();
    int mask = 0;
    for (uint64_t i = 0; i < len; ++i) {
        for (uint64_t j = 0; j < len; ++j) {
            mask ^= data[j];
        }
    }
    data[0] = mask;
}

void bubleSort1(std::vector<int>& data) {
    uint64_t len = data.size();
    int tmp;
    for (uint64_t i = 0; i < len; ++i) {
        for (uint64_t j = 0; j < len - 1; ++j) {
            if (data[j] > data[j + 1]) {
                tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}


void bubleSort2(std::vector<int>& data) {
    uint64_t len = data.size();
    int tmp;
    for (uint64_t i = len - 1; i; --i) {
        for (uint64_t j = 0; j < i; ++j) {
            if (data[j] > data[j + 1]) {
                tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}


void bubleSort3(std::vector<int>& data) {
    uint64_t i = data.size(), j;
    int tmp;
    bool unsorted = true;
    while (unsorted) {
        unsorted = false;
        --i;
        j = 0;
        while (j < i) {
            if (data[j] > data[j + 1]) {
                tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
                unsorted = true;
            }
            ++j;
        }

    }
}

void selectionSort2(std::vector<int>& data) {
    uint64_t n = data.size();
    int max1, max2;
    uint64_t i, j;

    //one pass in damb way. to enhure biigest elament at the end.
    max1 = data[0];
    for (i = 1; i < n - 1; ++i) {
        if (max1 < data[i]) {
            max2 = max1;
            max1 = data[i];
            data[i] = max2;
        }
    }
    if (data[n - 1] < max1) {
        data[0] = data[n - 1];
        data[n - 1] = max1;
    }
    else {
        data[0] = max1;
    }

    // [i:] slice is sorted finished region;
    for (i = n - 1; i; --i) {
        max1 = data[0];
        j = 0;
        while (true) {

            while (data[++j] <= max1);
            if (j == i) {
                data[0] = data[i - 1];
                data[i - 1] = max1;
                break;
            }
            max2 = data[j];
            data[j] = max1;

            while (data[++j] <= max2);
            if (j == i) {
                data[0] = data[i - 1];
                data[i - 1] = max2;
                break;
            }
            max1 = data[j];
            data[j] = max2;

        }
    }
}


bool order_cheack(std::vector<int> arr) {
    uint64_t n = arr.size() - 1;
    bool sorted = true;
    for (uint64_t i = 0; i < n; ++i) {
        sorted &= (arr[i] <= arr[i + 1]);
    }
    return sorted;
}



/*
TODO
1) добавить возможность проверки результата работы на коректность
2) добавить прослойку-обёртку для даных или сортировки, для подсчёта числа операций.
3) возможность warmup запусков. С тумблером для использование функций 1) и 2)

4) Проверить и отдебажить selectionSort2
*/
int main() {
    // Configuration
    int datasetSize = 1024;
    int mesurments = 16;
    int burstCount = 128;
    int warmupRounds = 16;
    unsigned seed = 42; // Fixed seed for reproducibility
    bool verbose_log = false;
    // Components Initialization
    auto datasets = DataSetGenerator::generate(burstCount + warmupRounds, datasetSize, seed);
    BenchmarkExecutor executor(mesurments, burstCount, warmupRounds);
    Logger logger("benchmark_ results.log", datasetSize, verbose_log);

    // Run benchmarks
    logger.set_algo("Linear reference");
    executor.run(linear_reference, datasets, logger);

    logger.set_algo("Square reference");
    executor.run(square_reference, datasets, logger);

    logger.set_algo("Buble Sort 1");
    executor.run(bubleSort1, datasets, logger);

    logger.set_algo("Buble Sort 2");
    executor.run(bubleSort2, datasets, logger);

    logger.set_algo("Buble Sort 3");
    executor.run(bubleSort3, datasets, logger);

    /*
        logger.set_algo("Quicksort");
        executor.run(quickSort, datasets, logger);

        logger.set_algo("Heapsort");
        executor.run(heapSort, datasets, logger);
    */

    /*
        char exit = 0;
        while (exit != 'q') {
            std::cin >> exit;
        }
        */
    return 0;
}
