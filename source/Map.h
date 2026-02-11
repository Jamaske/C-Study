#pragma once

#include <functional>
#include <list>
#include <stdint>
#include <string>
#include <utility>
#include <vector>

struct test demo[] =
    {
        {56,    23, "hello"},
        {-1, 93463, "world"},
        { 7,     5,    "!!"}
};

template <typename val_t>
class HashTableMap {
   public:
    HashTableMap()
        : HashTableMap(default_capacity) {}

    HashTableMap(size_t capacity = 101)
        : capacity(capacity),
          size(0),
          table(std::max(capacity, default_capacity)) {}

    bool insert(uint64_t key, const val_t& value);

    // Remove a key-value pair
    bool remove(const std::string& key);

    // Find a value by key
    bool find(const std::string& key, val_t& value) const;

   private:
    static const size_t default_capacity;
    size_t capacity;
    size_t size;
    std::vector<std::list<std::pair<std::string, val_t>>> table;

    // Resize the table when needed
    void resize() {
        for () {
        }
    }
};

template <typename val_t>
const size_t HashTableMap<val_t>::default_capacity = 16;