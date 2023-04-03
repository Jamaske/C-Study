#include <iostream>

typedef uint32_t ui;
typedef uint64_t ul;

int main(){
    ui N, K;
    std::cin >> N >> K;
    ui *arr = new ui[N];
    ui i = 0, j = 0, cur;
    ul Sum_betwen_ji, sub_arr_count = 1;

    std::cin >> cur;
    unsigned char zero = !cur;
    Sum_betwen_ji = cur;
    arr[0] = Sum_betwen_ji;

    for(; ++i < N;){
        std::cin >> cur;
        arr[i] = cur;
        zero += !cur;
        Sum_betwen_ji += cur;

        while(zero > 1 || Sum_betwen_ji > K && j <= i){
            cur = arr[j++];
            zero -= !cur;
            Sum_betwen_ji -= cur;
        }
        sub_arr_count += i - j + 1;

    }
    std::cout << sub_arr_count;
}