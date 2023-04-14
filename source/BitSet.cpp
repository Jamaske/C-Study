#include "BitSet.h"
#include <iostream>
#include <cstring>

BitSet::BitSet(size_t size, bool default_value) {
    bits = size;
    len = (size >> 6) + (bool)(bits & 0b111111);
    storage = new uint64_t [len];
    std::memset(storage, default_value * 0xFF, len * 8);
    storage[len-1] &= ~(-1 << (bits & 0b111111));
}

BitSet::BitSet(size_t size): BitSet(size, false){}

BitSet::BitSet(const BitSet &src): BitSet(src.bits){
    memcpy(storage, src.storage, len << 3);//каждый uint64 занимает 8 байт, поэтому << 3
}

BitSet::~BitSet() {
    delete[] storage;
}

void BitSet::log(){
    std::cout << "BitSet: " <<  this << " log\n";
    uint64_t  el;
    for(size_t i = len; i-->0;){
        el = storage[i];
        for(uint_fast8_t j = 64; j-->0;){
            std::cout<< (bool)(el & ((uint64_t)1 << j));
        }
        std::cout << '\t' << el << '\n';
    }
    std::cout << '\n';
}


BitSet &BitSet::operator=(const BitSet &ref) {
    if(this != &ref){
        bits = ref.bits;
        if(len != ref.len){
            len = ref.len;
            delete[] storage;
            storage = new uint64_t [len];
        }
        memcpy(storage, ref.storage, len << 3);
    }
    return *this;
}

BitSet &BitSet::operator=(BitSet &&ref){
    if(this != &ref){
        std::swap(bits, ref.bits);
        std::swap(len, ref.len);
        std::swap(storage, ref.storage);
    }
    return *this;
}

bool BitSet::operator[](size_t idx) {
    return (bool)( *(storage + (idx >> 6)) & (1 << (idx & 0b111111)) );
}

void BitSet::set_to(size_t idx, bool state) {
    uint64_t *el = (storage + (idx >> 6 ));
    uint_fast64_t shift = idx & 0b111111;
    *el &= ~(1 << shift);//обнуление
    *el |= (state << shift);//записываем нужное значение
}

void BitSet::flip(size_t idx) {
    *(storage + (idx >> 6)) ^= (1 << (idx & 0b111111));
}

BitSet BitSet::operator|(const BitSet & RHS){
    BitSet ret(std::max(bits, RHS.bits));

    //копирование не пересекающихся частей можно попробовать переписать через memcpy
    for (size_t i = ret.len; i-- > len;){
        ret.storage[i] = RHS.storage[i];
    }
    for (size_t i = ret.len; i-- > RHS.len;){
        ret.storage[i] = this->storage[i];
    }

    for(size_t i = 0; i < std::min(len, RHS.len); ++i){
        ret.storage[i] = this->storage[i] | RHS.storage[i];
    }
    return ret;
}

BitSet BitSet::operator&(const BitSet &RHS) {
    BitSet ret(std::max(bits, RHS.bits));
    //зануленное непересекающихся частей делать не нужно
    for(size_t i = 0; i < std::min(len, RHS.len); ++i){
        ret.storage[i] = this->storage[i] & RHS.storage[i];
    }
    return ret;

}

BitSet BitSet::operator^(const BitSet &RHS) {
    BitSet ret(std::max(bits, RHS.bits));

    //копирование не пересекающихся частей
    for (size_t i = ret.len; i-- > len;){
        ret.storage[i] = RHS.storage[i];
    }
    for (size_t i = ret.len; i-- > RHS.len;){
        ret.storage[i] = this->storage[i];
    }

    for(size_t i = 0; i < std::min(len, RHS.len); ++i){
        ret.storage[i] = this->storage[i] ^ RHS.storage[i];
    }
    return ret;
}