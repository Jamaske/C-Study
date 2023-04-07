#include "BitSet.h"
#include <iostream>

BitSet::BitSet(size_t size, bool default_value) {
    default_value = default_value ? 0xFFFFFFFFFFFFFFFF:0;
    bits = size;
    len = (size >> 6) + (bool)(size & 0b111111);
    storage = new uint64_t [size] {default_value};
}

BitSet::BitSet(size_t size): BitSet(size, false) {
    bits = size;
    len = (size >> 6) + (bool)(size & 0b111111);
    storage = new uint64_t [size] {0};
}

BitSet::BitSet(const BitSet &src): BitSet(src.bits){
    memcpy(storage, src.storage, len << 3);//каждый uint64 занимает 8 байт, поэтому << 3
}

BitSet::~BitSet() {
    delete[] storage;
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
        ret.storage[i] = this->storage[i] | RHS.storage[i];
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



/*BitSet &BitSet::operator<<(size_t shift) {
    BitSet ret(bits);
    size_t block_shift = shift >> 6;
    uint_fast16_t bit_shift = shift & 0x111111;
    uint64_t carry = 0, block;

    for(size_t i = block_shift; i < ret.len; ++i){
        ret.storage[i] = carry;
        block = storage[i - block_shift];
        carry = block >> (64 - bit_shift);
    }
}*/




