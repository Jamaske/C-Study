#pragma once
#include <cstdint>
//source
class BitSet{
    uint64_t* storage;
    size_t len; //number of storage's elements
    size_t bits;

public:
    BitSet(size_t size);
    BitSet(const BitSet& src);
    ~BitSet();

    BitSet& operator=(const BitSet& ref);
    bool operator[](size_t idx);

    void set_to(size_t idx, bool state);//set a bit at given index to given state
    void flip(size_t idx);//invert a bit at given index

    BitSet& operator|(const BitSet& RHS);
    BitSet& operator&(const BitSet& RHS);
    BitSet& operator^(const BitSet& RHS);
    //BitSet& operator<<(size_t shift); //тяжко
};