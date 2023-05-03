#include <iostream>

typedef uint8_t uc;
typedef uint64_t ul;

ul items[60];
ul max_sum[60];

ul combinations(ul target_sum, uc item_idx){
    ul comb = 0;
    ul cur_item = items[item_idx];
    ul potential_addition = max_sum[item_idx];
    comb
}


int main (){
    uc n;
    ul W;
    std::cin >> n >> W;
    ul cur_item;
    ul sum = 0;
    for(uc i = 0; i < n; ++i){
        std::cin >> cur_item;
        sum += 2 * cur_item;
        items[i] = cur_item;
        max_sum[i] = sum;
    }

}