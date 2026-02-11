/*
Задача - поиск анограмм
1) дана сторока S длинны n
2) дана референс-строка T длинны m
3) m <= n <= 10^9
4) строки используют аски символы (|w| <= 128)
Написать функцию, возвращающю первый индексы начала подстрок S длинны m, являющихся анограммой (буквенными перестановками) строки T
Оптимизировать по времени
*/
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
std::ostringstream find_anagram(std::string S, std::string T) {
    std::ostringstream answers;
    int32_t cnts[26] = {};
    int32_t* cnts_a_off = cnts - 'a';
    for (char ch : T) --cnts_a_off[ch];
    size_t i;
    for (i = 0; i < T.size(); ++i) ++cnts_a_off[S[i]];
    uint64_t non_zeros_cnt = 0;
    for (i = 0; i < 26; ++i)
        non_zeros_cnt += bool(cnts[i]);
    char* F = S.data() + T.size();
    for (i = 0; i < S.size() - T.size();)
        if (!(non_zeros_cnt += !cnts_a_off[F[i]] - !++cnts_a_off[F[i]] + !cnts_a_off[S[i]] - !--cnts_a_off[S[i++]])) answers << i << ' ';

    return std::move(answers);
}


// Драйвер код
int main() {
    auto result = find_anagram("aaaabacbaabababab", "aabb");
    std::cout << result.str() << "\b\n";
}