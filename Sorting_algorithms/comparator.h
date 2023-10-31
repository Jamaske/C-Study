#pragma once
#include <cstdint>

template<typename T> struct comparator {comparator():cmp_count(0){}
    std::uint64_t cmp_count;
    /**@param A @param B @return if A > B*/ bool GreaterThen(T A, T B){++cmp_count; return A > B;}
    /**@param A @param B @return if A >= B*/ bool GreaterOrEqual(T A, T B) {++cmp_count; return A >= B;}
    /**@param A @param B @return if A < B*/ bool LessThen(T A, T B) {++cmp_count; return A < B;}
    /**@param A @param B @return if A <= B*/ bool LessOrEqual(T A, T B) {++cmp_count; return A <= B;}
};