#include <iostream>

typedef uint32_t ui;
typedef uint64_t ul;

int main(){
    ui N, K;
    std::cin >> N >> K;
    ui *arr = new ui[N];
    ui i = 0, j = 0, zero_idx = 0, cur;
    ul Sum_betwen_ji, Sum_betwen_jzero = 0, sub_arr_count = 1;
    bool zero_in_sub;

    std::cin >> cur;
    zero_in_sub = !cur;
    Sum_betwen_ji = cur;
    arr[0] = Sum_betwen_ji;

    for(; ++i < N;){
        std::cin >> cur;
        arr[i] = cur;

        if (cur == 0){
            if(zero_in_sub){
                Sum_betwen_ji -=Sum_betwen_jzero;
                j = zero_idx + 1;
            }
            zero_in_sub = true;
            zero_idx = i;
            Sum_betwen_jzero = Sum_betwen_ji;
        }

        Sum_betwen_ji += cur;

        while(Sum_betwen_ji > K && j <= i){
            cur = arr[j++];
            zero_in_sub = (bool)cur;
            Sum_betwen_ji -= cur;
            Sum_betwen_jzero -= cur;
        }
        sub_arr_count += i - j + 1;

    }
    std::cout << sub_arr_count;
}