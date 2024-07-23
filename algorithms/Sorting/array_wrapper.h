#pragma once
#include <cstdint>

struct operation_count{
    std::uint64_t rnd_reads;
    std::uint64_t rnd_writes;
    std::uint64_t con_reads;
    std::uint64_t con_writes;
    operation_count():rnd_reads(0), rnd_writes(0),con_reads(0), con_writes(0){}
};

template<typename T>
class array_wrapper {
private:
    T& array;
    std::uint32_t size;
public:
    operation_count telemetry;
    array_wrapper(T &array, std::uint32_t size):array(array), size(size),telemetry(operation_count()){}
    T get(std::uint32_t idx) {++telemetry.rnd_reads; return array[idx];}
    void put(std::uint32_t idx, T value){++telemetry.rnd_writes; array[idx] = value;}
};

template<typename T>
struct iter{
    operation_count& telemetry_ref;
    T* idx;
    iter(array_wrapper<T>& array, std::uint32_t start):
    idx(&(array[start])), telemetry_ref(array.telemetry){}
    void operator++(){++idx;}
    void operator--(){--idx;}
    T get(){++telemetry_ref.con_reads; return *idx;}
    void put(T value){++telemetry_ref.con_writes; *idx = value;}
};