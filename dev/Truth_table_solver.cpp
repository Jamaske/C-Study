#include <unordered_set>
#include <cstdint>
#include <vector>
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <iomanip>



typedef std::uint8_t u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;
typedef u16 expr;

constexpr u8 arg_num = 4;
constexpr u8 interpritations_num = (1 << arg_num);
constexpr u8 solution_operation_limit = 8;
constexpr u8 solution_max_len = arg_num + solution_operation_limit;
//constexpr u16 negate = 0b1111'1111'1111'1111;


//7 segment signals
static std::unordered_set<expr> requests = {
        0b1011011111101011,
        0b1111100111100100,
        0b1101111111110100,
        0b1011011011011110,
        0b1010001010111111,
        0b1000111011111011,
        0b0011111011110111
};

/*
//equal
static std::unordered_set<expr> requests = {
        0b0000'0000'0000'0110,
        0b0000'0000'0000'0001,
};
*/
//initializing all data storage

//course's single permited operation
static u64 nand_calls = 0;
inline expr nand(expr a, expr b) { return ~(++nand_calls, a & b); }



//data structures types
template<typename T>
struct vector_set {
    std::vector<T> vector;
    std::unordered_set<T> set;

    vector_set() {
        vector = std::vector<T>();
        set = std::unordered_set<T>();
    }

    vector_set(std::size_t size) {
        vector = std::vector<T>(size);
        set = std::unordered_set<T>(size);
    }


    bool add(T el) {
        if (set.insert(el).second) {
            vector.push_back(el);
            return true;
        }
        return false;
    }

    T pop() {
        T el = vector.back();
        set.erase(el);
        vector.pop_back();
        return el;
    }

    T& operator[](std::size_t idx) {
        return vector[idx];
    }

    bool contains(T el) const {
        return set.contains(el);
    }

    std::size_t size() const {
        return vector.size();
    }

    void print() {
        for (std::size_t i = 0; i < vector.size(); ++i) {
            std::cout << std::setw(3) << i << ' ' << std::bitset<sizeof(T) * 8>(vector[i]) << " = " << vector[i] << '\n';
        }
    }
};

template<typename T>
struct vector_map
{
    std::vector<T> vector;
    std::unordered_map<T, u64 > map;
    vector_map() {
        vector = std::vector<T>();
        map = std::unordered_map<T, u64>();
    }

    vector_map(std::size_t size) {
        vector = std::vector<T>(size);
        map = std::unordered_map<T, u64>(size);
    }

    bool append(T el) {
        if (map.contains(el)) return false;
        map[el] = vector.size();
        vector.push_back(el);
        return true;
    }

    T pop() {
        T el = vector.back();
        vector.pop_back();
        map.erase(el);
        return el;
    }

    T& operator[](std::size_t idx) {
        return vector[idx];
    }

    bool contains(T el) const {
        return map.contains(el);
    }

    std::size_t size() const {
        return vector.size();
    }

    std::size_t idxof(T el) {
        if (map.contains(el)) return map.at(el);
        return -1;
    }

    void print() {
        for (std::size_t i = 0; i < vector.size(); ++i) {
            std::cout << i << ' ' << std::bitset<sizeof(T) * 8>(vector[i]) << " = " << vector[i] << '\n';
        }
    }
};


struct solution {

    //parseing solution sequence, restoreing operation order, checking for validyty
    static u64 validate_solution_calls;
    static bool validate_solution(std::vector<expr>& solution, bool verbose) {
        ++validate_solution_calls;

        u8 validated_idx, i, j;
        expr validated_value, a, b, res;
        std::cout << '\n';
        for (validated_idx = arg_num; validated_idx < solution.size(); ++validated_idx) {
            validated_value = solution[validated_idx];
            for (i = 0; i < validated_idx; ++i) {
                a = solution[i];
                for (j = i; j < validated_idx; ++j) {
                    b = solution[j];
                    res = nand(a, b);
                    if (res == validated_value) {
                        if (verbose) std::cout << std::bitset<sizeof(expr) * 8>(a) << '\n' << std::bitset<sizeof(expr) * 8>(b) << '\n' << std::bitset<sizeof(expr) * 8>(res) << "\n\n";
                        goto next_iter;
                    }
                }
            }
            //invalid exit
            std::cout << validated_idx << " error " << validated_value << std::endl;
            return false;
            //valid continuation
        next_iter:
        }
        std::cout << "Valid " << std::endl;
        return true;
    }

    //partial solutions
    static std::unordered_map<expr, std::vector<expr>> partial_solutions;
    static u64 update_partial_solution_calls;
    static void update_partial_solution(expr signal, vector_set<expr>& new_solution) {
        ++update_partial_solution_calls;

        if (partial_solutions[signal].size() > new_solution.size() && validate_solution(new_solution.vector, false)) {
            partial_solutions[signal] = new_solution.vector;
            std::cout << "partial solution\n";
            new_solution.print();
            std::cout << std::endl;
        }
    }

    //full solution (houpfully)
    static std::vector<expr> full_solution;
    static u64 update_full_solution_calls;
    static void update_full_solution(vector_set<expr>& new_solution) {
        if (full_solution.size() > new_solution.size() && validate_solution(new_solution.vector, false)) {
            full_solution = new_solution.vector;
            std::cout << "!!!new full solution!!!\n";
            new_solution.print();
            std::cout << "=======================" << std::endl;
        }
    }

    static void initialize() {
        std::vector<expr> full_solution(solution_max_len, 0);
        std::unordered_map<expr, std::vector<expr>> partial_soliton;
        for (expr i : requests) {
            partial_solutions[i] = full_solution;
        }
    }

};
u64 solution::validate_solution_calls = 0;
u64 solution::update_partial_solution_calls = 0;
u64 solution::update_full_solution_calls = 0;


//main recursion function
template<typename T>
struct solver {
    static vector_set<u16> stack;
    static u64 k0, k1, k2;

    template<int depth>
    void combine(u64 i, u64 j) {//u64 just for better alligment
        if ((++j > i) && (j = 0, ++i > depth + arg_num)) return;
        T product;
        do {
            do {
                product = nand(stack[i], stack[j]);
                if (stack.contains(product)) continue;
                stack.add(product);

                if (requests.contains(product)) {
                    solution::update_partial_solution(product, stack);
                    //check if this is new full solution
                    for (const T& el : requests) {
                        if (!stack.contains(el)) {
                            //early comparison exit
                            goto exit;
                        }
                    }
                    //keep the shortest full solution
                    solution::update_full_solution(stack);
                }exit:

                combine<depth + 1>(i, j);
                stack.pop();
            } while (++j <= i);
        } while (j = 0, ++i < depth + arg_num);
    }

    template<T>
    void combine<0>(u64 i, u64 j) {
        T product;
        k0 = 0;

        do {
            do {
                product = nand(stack[i], stack[j]);
                if (stack.contains(product)) continue;
                ++k0;
                //std::cout<< k0++ << ' ' << k1 << ' ' << k2 <<std::endl;
                stack.add(product);

                if (requests.contains(product)) {
                    solution::update_partial_solution(product, stack);
                    //check if this is new full solution
                    for (const T& el : requests) {
                        if (!stack.contains(el)) {
                            //early comparison exit
                            goto exit;
                        }
                    }
                    //keep the shortest full solution
                    solution::update_full_solution(stack);

                }exit:

                combine<1>(i, j);
                stack.pop();
            } while (++j <= i);
        } while (j = 0, ++i < arg_num);
    }

    template<>
    void combine<1>(u64 i, u64 j) {
        T product;
        k1 = 0;

        if ((++j > i) && (j = 0, ++i > 1 + arg_num)) return;
        do {
            do {
                product = nand(stack[i], stack[j]);
                if (stack.contains(product)) continue;
                ++k1;
                //std::cout<< k0 << ' ' << k1++ << ' ' << k2 <<std::endl;
                stack.add(product);

                if (requests.contains(product)) {
                    solution::update_partial_solution(product, stack);
                    //check if this is new full solution
                    for (const T& el : requests) {
                        if (!stack.contains(el)) {
                            //early comparison exit
                            goto exit;
                        }
                    }
                    //keep the shortest full solution
                    solution::update_full_solution(stack);
                }exit:

                combine<2>(i, j);
                stack.pop();
            } while (++j <= i);
        } while (j = 0, ++i < 1 + arg_num);
    }

    template<>
    void combine<2>(u64 i, u64 j) {
        T product;
        k2 = 0;

        if ((++j > i) && (j = 0, ++i > 2 + arg_num)) return;
        do {
            do {
                product = nand(stack[i], stack[j]);
                if (stack.contains(product)) continue;
                std::cout << k0 << ' ' << k1 << ' ' << ++k2 << " cals: " << nand_calls << std::endl;
                stack.add(product);

                if (requests.contains(product)) {
                    solution::update_partial_solution(product, stack);
                    //check if this is new full solution
                    for (const T& el : requests) {
                        if (!stack.contains(el)) {
                            //early comparison exit
                            goto exit;
                        }
                    }
                    //keep the shortest full solution
                    solution::update_full_solution(stack);
                }exit:

                combine<3>(i, j);
                stack.pop();
            } while (++j <= i);
        } while (j = 0, ++i < 2 + arg_num);
    }

    template<>
    void combine<solution_operation_limit>(u64 i, u64 j) {
        T product;

        if ((++j > i) && (j = 0, ++i > solution_operation_limit + arg_num)) return;
        do {
            do {
                product = nand(stack[i], stack[j]);
                if (stack.contains(product)) continue;
                stack.add(product);

                if (requests.contains(product)) {
                    solution::update_partial_solution(product, stack);
                    //check if this is new full solution
                    for (const T& el : requests) {
                        if (!stack.contains(el)) {
                            //early comparison exit
                            goto exit;
                        }
                    }
                    //keep the shortest full solution
                    solution::update_full_solution(stack);

                }exit:

                stack.pop();
            } while (++j <= i);
        } while (j = 0, ++i < solution_operation_limit + arg_num);
    }
}








int main() {

    {//initialization of a stack
        u16 i = interpritations_num;
        T a = -1;
        //vector_set tmp;
        while (i >>= 1) {
            a ^= (a << i);
            stack.add(a);
        }
        std::cout << "Input signals truth tables\n";
        stack.print();

    }
    solution::initialize();
    std::cout << "Recursion depth:" << solution_operation_limit << '\n';

    combine<0>(0, 0);

    std::cout << "============FULL==RESULTS============" << '\n';
    for (auto i : solution::full_solution) {
        std::cout << std::bitset<sizeof(T) * 8>(i) << '\n';
    }
    validate_solution<u16>(solution::full_solution, true);

    std::cout << "============PARTIAL==RESULTS============" << '\n';
    for (T i : requests) {
        std::cout << "for signal: " << i << '\n';
        for (T j : solution::partial_solutions[i]) {
            std::cout << std::bitset<sizeof(T) * 8>(j) << '\n';
        }
        validate_solution<u16>(solution::partial_solutions[i], true);

    }
    std::cout << "total nand cals: " << nand_calls << '\n' << "PRESS ENTER TO EXIT\n";
    char a;
    std::cin >> a;
}