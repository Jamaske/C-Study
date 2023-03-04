#include <iostream>
#include <string>

std::string expand_brackets(){
    static unsigned read_idx;
    static std::string input;
    unsigned tmp_idx = read_idx;
    while(input[read_idx] != '['){
        read_idx++;
    }
    std::cout << input.substr(tmp_idx, read_idx - tmp_idx);

    int iterations = std::stoi(input.substr(tmp_idx, read_idx - tmp_idx));
    tmp_idx++;

    std::cout << iterations << input[read_idx];

}

int main(){
    static std::string input;
    std::cin >> input;
    static unsigned read_idx = 0;

    expand_brackets();


}