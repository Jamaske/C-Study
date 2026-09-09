//
// Created by Master on 20.10.2023.
//

#include <chrono>
#include <string>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <array>
#include <cmath>

__attribute__((used))
uint64_t bin_to_bcd(uint64_t bin, const uint8_t first_1_idx = 53) {
    if (bin > 9999999999999999) return -1;
    if (first_1_idx > 53) return -2;

    uint8_t bit = first_1_idx - 1;
    uint64_t expression;
    while (bit >= 5) {
        expression = (((bin >> 0) | (bin >> 1)) & (bin >> 2) | (bin >> 3)) & 0x1111111111111111 << --bit;
        bin += expression | expression << 1;

        expression = (((bin >> 0) | (bin >> 1)) & (bin >> 2) | (bin >> 3)) & 0x1111111111111111 << --bit;
        bin += expression | expression << 1;

        expression = (((bin >> 0) | (bin >> 1)) & (bin >> 2) | (bin >> 3)) & 0x1111111111111111 << --bit;
        bin += expression | expression << 1;

        expression = (((bin >> 0) | (bin >> 1)) & (bin >> 2) | (bin >> 3)) & 0x1111111111111111 << --bit;
        bin += expression | expression << 1;
    }
    switch (bit) {
    case 4:
        expression = (((bin >> 0) | (bin >> 1)) & (bin >> 2) | (bin >> 3)) & 0x1111111111111111 << 3;
        bin += expression | expression << 1;
    case 3:
        expression = (((bin >> 0) | (bin >> 1)) & (bin >> 2) | (bin >> 3)) & 0x1111111111111111 << 2;
        bin += expression | expression << 1;
    case 2:
        expression = (((bin >> 0) | (bin >> 1)) & (bin >> 2) | (bin >> 3)) & 0x1111111111111111 << 1;
        bin += expression | expression << 1;
    }
    return bin;
}
__attribute__((used))
char* bcd_to_charr(uint64_t bcd, uint8_t charr_len = 16) {
    char* charr = new char[charr_len + 1];
    charr[charr_len] = 0;
    uint64_t bit = charr_len * 4;
    uint64_t char_cnt = 0;

next:
    switch (char_cnt) {
    default:
        charr[char_cnt++] = (char)((bcd >> (bit -= 4) & 0x000000000000000F) + 48);
    case 13:
        charr[char_cnt++] = (char)((bcd >> (bit -= 4) & 0x000000000000000F) + 48);
    case 14:
        charr[char_cnt++] = (char)((bcd >> (bit -= 4) & 0x000000000000000F) + 48);
    case 15:
        charr[char_cnt++] = (char)((bcd >> (bit -= 4) & 0x000000000000000F) + 48);
        goto next;
    case 16:;
    }
    return charr;
}

__attribute__((used))
void bin_to_charr(uint64_t bin) {
    bcd_to_charr(bin_to_bcd(bin));
    return;
}


struct Timer {

    uint64_t bunch_size, bunch_num, warm_up, bunch_counter, arg_start;
    void (*func)(uint64_t arg);
    std::chrono::_V2::system_clock::time_point(*time_stamps)[4];
    std::chrono::nanoseconds(*durations)[3];
    std::chrono::nanoseconds sums[3] = { std::chrono::nanoseconds(0) };
    std::chrono::nanoseconds squre_sums[3] = { std::chrono::nanoseconds(0) };
    std::chrono::nanoseconds averege[3] = { std::chrono::nanoseconds(0) };
    std::chrono::nanoseconds std_div[3] = { std::chrono::nanoseconds(0) };

    Timer(uint64_t bunch_size, uint64_t bunch_num, uint64_t warm_up, void (*func)(uint64_t arg), uint64_t arg_start) {
        this->bunch_size = bunch_size;
        this->bunch_num = bunch_num;
        this->warm_up = warm_up;
        this->bunch_counter = 0;
        this->func = func;
        this->arg_start = arg_start;
        this->time_stamps = new std::chrono::_V2::system_clock::time_point[bunch_num][4];
    }

    void bunch_run_1() {
        time_stamps[bunch_counter][0] = std::chrono::high_resolution_clock::now();
        for (uint64_t i = arg_start; i < bunch_size + arg_start;) {
            func(i++);
        }
        time_stamps[bunch_counter][1] = std::chrono::high_resolution_clock::now();
    }

    void bunch_run_2() {
        time_stamps[bunch_counter][2] = std::chrono::high_resolution_clock::now();
        for (uint64_t i = arg_start; i < (bunch_size + arg_start) * 2;) {
            func(i++);
            func(i++);
        }
        time_stamps[bunch_counter][3] = std::chrono::high_resolution_clock::now();
    }

    void analize() {
        for (uint64_t i = warm_up; i < bunch_num; ++i) {
            durations[i][0] = std::chrono::duration_cast<std::chrono::nanoseconds>(time_stamps[i][1] - time_stamps[i][0]) / bunch_size;
            durations[i][1] = std::chrono::duration_cast<std::chrono::nanoseconds>(time_stamps[i][3] - time_stamps[i][2]) / bunch_size;
            durations[i][2] = std::chrono::duration_cast<std::chrono::nanoseconds>(durations[i][1] - durations[i][0]);
            for (uint64_t j = 0; j < 3; ++j) {
                sums[j] += durations[i][j];
                squre_sums[j] += std::chrono::nanoseconds((uint64_t)(durations[i][j].count() * durations[i][j].count()));

            }
        }
        for (uint64_t i = 0; i < 3; ++i) {
            averege[i] = sums[i] / bunch_num;
            std_div[i] = std::chrono::nanoseconds((uint64_t)std::sqrt((squre_sums[i].count() - sums[i].count() * sums[i].count() / bunch_num) / bunch_num));
        }
    }

    void print_breaf() {
        for (uint64_t i = 0; i < 3; ++i)
        {
            std::cout << i << " - avarage nanoseconds " << averege[i] << " with std div of nanoseconds " << std_div[i] << std::endl;
        }
    }

    void run() {
        bunch_run_1();
        bunch_run_2();
        analize();
        print_breaf();
    }
};



int main() {
    Timer timer(1 << 16, 1 << 16, 1 << 7, bin_to_charr, 1 << 10);
    timer.run();
    char dymmy;
    std::cin >> dymmy;
    return 0;
}
