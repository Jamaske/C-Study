#pragma once
#include <cstdint>
class BitSet{
    uint64_t* storage;
    size_t len; //number of storage's elements
    size_t bits;//number of allocated bits

public:
    explicit BitSet(size_t size);
    explicit BitSet(size_t size, bool default_value);
    BitSet(const BitSet& src);
    ~BitSet();

    void log();
    //get &Rvalue and copy by value
    BitSet& operator=(const BitSet& ref);
    //get ref to a &Rvalue and swap their contents
    //ref to &Rvalue is a template object, so it might be rewritten
    //it will be destroyed later anyway
    BitSet& operator=(BitSet&& ref);
    bool operator[](size_t idx);

    void set_to(size_t idx, bool state);//set a bit at given index to given state
    void flip(size_t idx);//invert a bit at given index

    BitSet operator|(const BitSet& RHS);
    BitSet operator&(const BitSet& RHS);
    BitSet operator^(const BitSet& RHS);
    //BitSet& operator<<(size_t shift); //тяжко
};

/*
//example of use
#include <iostream>
int main(){
    std::cout << "make bitsets with general constructor\n\n";
    BitSet obj1(70);
    BitSet obj2(70, true);
    obj1.log();
    obj2.log();

    std::cout << "get and manipulate with certain bit\n\n";
    obj1.log();
    std::cout << obj1[65] << '\n';
    obj1.set_to(65, true);
    std::cout << obj1[65] << '\n';
    obj1.flip(65);
    std::cout << obj1[65] << '\n';


    std::cout << "use assignment operator\n\n";
    obj1 = obj2;
    obj1.log();
    obj2.log();
    std::cout << "check for copying by value\n\n";
    obj1.flip(65);
    obj2.flip(2);
    obj1.log();
    obj2.log();

    std::cout << "use copy constructor\n\n";
    BitSet obj3(obj1);
    obj3.log();
    std::cout << "check for copying by value\n\n";
    obj3.flip(5);
    obj1.flip(68);
    obj1.log();
    obj3.log();

    std::cout << "perform bitwise operations\n\n";
    obj3 = obj1 & obj2;
    obj3.log();
}
 */