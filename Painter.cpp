#include <iostream>

int main(){
    int N;
    unsigned int max_idx = 0, min_idx = 0;
    long long max, min, cur;
    std::cin >> N;
    std::cin >> max;
    min = max;
    for(unsigned int i = 1; i < N; ++i){
        std::cin >> cur;
        if(max <= cur){
            max = cur;
            max_idx = i;
        }
        if(min > cur){
            min = cur;
            min_idx = i;
        }

    }
    std::cout << max_idx + 1 << ' '  << min_idx + 1 << '\n';
}