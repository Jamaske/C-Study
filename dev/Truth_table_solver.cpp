#include <unordered_set>
#include <cstdint>
#include <vector>
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <iomanip>


#define T  us

#define MAX_DEPTH 10
typedef std::uint16_t us;
typedef std::uint64_t ul;
constexpr int n = 4;
constexpr int s = (1 << n);
constexpr T negate = 0b1111'1111'1111'1111;

static ul nand_calls = 0;
inline T nand (T a, T b){
    ++nand_calls;
    return negate ^ (a & b);
}
bool validate_solution(std::vector<T>& solution, bool verbose){
    ul validate, i, j;
    T a, b, res, req;
    std::cout << '\n';
    for(validate = n; validate < solution.size(); ++validate){
        req = solution[validate];
        for(i = 0; i < validate; ++i){
            a = solution[i];
            for(j = i; j < validate; ++j){
                b = solution[j];
                res = nand(a, b);
                if(res == req){
                    if(verbose) std::cout << std::bitset<sizeof(T) * 8>(a)<< '\n' << std::bitset<sizeof(T) * 8>(b) << '\n' << std::bitset<sizeof(T) * 8>(res) << "\n\n";
                    goto next_iter;
                }
            }
        }
        //invalid exit
        std::cout << validate << " error " << req << std::endl;
        return false;

        next_iter:
    }
    std::cout << "Valid ";
    return true;
}

//data structures types
struct vector_set{
    std::vector<T> vector;
    std::unordered_set<T> set;
    vector_set(){
        vector = std::vector<T>();
        set = std::unordered_set<T>();
    }


    bool add(T el){
        if(set.contains(el)) return false;
        vector.push_back(el);
        set.insert(el);
        return true;
    }

    T pop(){
        T el = vector.back();
        vector.pop_back();
        set.erase(el);
        return el;
    }

    T& operator[](std::size_t idx){
        return vector[idx];
    }

    bool contains(T el) const{
        return set.contains(el);
    }

    std::size_t size() const{
        return vector.size();
    }

    void print(){
        for(std::size_t i = 0; i < vector.size(); ++i){
            std::cout << std::setw(3) << i << ' ' << std::bitset<sizeof(T) * 8>(vector[i]) << " = " << vector[i] << '\n';
        }
    }
};
struct vector_map
{
    std::vector<T> vector;
    std::unordered_map<T,ul > map;
    vector_map() {
        vector = std::vector<T>();
        map = std::unordered_map<T, ul>();
    }

    bool append(T el){
        if(map.contains(el)) return false;
        map[el] = vector.size();
        vector.push_back(el);
        return true;
    }

    T pop(){
        T el = vector.back();
        vector.pop_back();
        map.erase(el);
        return el;
    }

    T& operator[](std::size_t idx){
        return vector[idx];
    }

    bool contains(T el) const{
        return map.contains(el);
    }

    std::size_t size() const{
        return vector.size();
    }

    void print(){
        for(std::size_t i = 0; i < vector.size(); ++i){
            std::cout << i << ' ' << std::bitset<sizeof(T) * 8>(vector[i]) << " = " << vector[i] << '\n';
        }
    }
};

//7 segment signals
static std::unordered_set<T> requests = {
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
static std::unordered_set<T> requests = {
        0b0000'0000'0000'0110,
        0b0000'0000'0000'0001,
};
*/
//initializing all data storage
struct solution{
    static std::unordered_map<T, std::vector<T>> partial_solutions;
    static std::vector<T> full_solution;
    static void update_partial_solution(T signal, vector_set& new_solution){

        if(partial_solutions[signal].size() > new_solution.size() && validate_solution(new_solution.vector, false) ){
            partial_solutions[signal] = new_solution.vector;
            std::cout << "partial solution\n";
            new_solution.print();
            std::cout << std::endl;
        }
    }
    static void update_full_solution(vector_set& new_solution){
        if(full_solution.size() > new_solution.size() && validate_solution(new_solution.vector, false)){
            full_solution = new_solution.vector;
            std::cout << "!!!new full solution!!!\n";
            new_solution.print();
            std::cout << "=======================" << std::endl;
        }
    }
    static void initialize(){
        std::vector<T> tmp;
        for(us i = 0; i < MAX_DEPTH + 10; ++i){
            tmp.push_back(0);
        }
        full_solution = tmp;
        for(T i: requests){
            partial_solutions[i] = tmp;
        }
    }
};
std::unordered_map<T, std::vector<T>> solution::partial_solutions;
std::vector<T> solution::full_solution;
static vector_set stack;

static ul k0, k1, k2;
//main recursion function
template<int depth>
void combine(ul i, ul j){
    T product;

    if((++j > i) && (j = 0, ++i > depth + n)) return;
    do{
        do{
            product = nand(stack[i], stack[j]);
            if(stack.contains(product)) continue;
            stack.add(product);

            if(requests.contains(product)){
                solution::update_partial_solution(product, stack);
                //check if this is new full solution
                for(const T& el : requests){
                    if(!stack.contains(el)){
                        //early comparison exit
                        goto exit;
                    }
                }
                //keep the shortest full solution
                solution::update_full_solution(stack);
            }exit:

            combine<depth + 1>(i,j);
            stack.pop();
        }while(++j <= i);
    }while(j = 0, ++i < depth + n);
}

template<>
void combine<MAX_DEPTH>(ul i, ul j){
    T product;

    if((++j > i) && (j = 0, ++i > MAX_DEPTH + n)) return;
    do{
        do{
            product = nand(stack[i], stack[j]);
            if(stack.contains(product)) continue;
            stack.add(product);

            if(requests.contains(product)){
                solution::update_partial_solution(product, stack);
                //check if this is new full solution
                for(const T& el : requests){
                    if(!stack.contains(el)){
                        //early comparison exit
                        goto exit;
                    }
                }
                //keep the shortest full solution
                solution::update_full_solution(stack);

            }exit:

            stack.pop();
        }while(++j <= i);
    }while(j = 0, ++i < MAX_DEPTH + n);
}

template<>
void combine<2>(ul i, ul j){
    T product;
    k2 = 0;

    if((++j > i) && (j = 0, ++i > 2 + n)) return;
    do{
        do{
            product = nand(stack[i], stack[j]);
            if(stack.contains(product)) continue;
            std::cout<< k0 << ' ' << k1 << ' ' << ++k2 << " cals: " << nand_calls <<std::endl;
            stack.add(product);

            if(requests.contains(product)){
                solution::update_partial_solution(product, stack);
                //check if this is new full solution
                for(const T& el : requests){
                    if(!stack.contains(el)){
                        //early comparison exit
                        goto exit;
                    }
                }
                //keep the shortest full solution
                solution::update_full_solution(stack);
            }exit:

            combine<3>(i, j);
            stack.pop();
        }while(++j <= i);
    }while(j = 0, ++i < 2 + n);
}

template<>
void combine<1>(ul i, ul j){
    T product;
    k1 = 0;

    if((++j > i) && (j = 0, ++i > 1 + n)) return;
    do{
        do{
            product = nand(stack[i], stack[j]);
            if(stack.contains(product)) continue;
            ++k1;
            //std::cout<< k0 << ' ' << k1++ << ' ' << k2 <<std::endl;
            stack.add(product);

            if(requests.contains(product)){
                solution::update_partial_solution(product, stack);
                //check if this is new full solution
                for(const T& el : requests){
                    if(!stack.contains(el)){
                        //early comparison exit
                        goto exit;
                    }
                }
                //keep the shortest full solution
                solution::update_full_solution(stack);
            }exit:

            combine<2>(i, j);
            stack.pop();
        }while(++j <= i);
    }while(j = 0, ++i < 1 + n);
}

template<>
void combine<0>(ul i, ul j){
    T product;
    k0 = 0;

    do{
        do{
            product = nand(stack[i], stack[j]);
            if(stack.contains(product)) continue;
            ++k0;
            //std::cout<< k0++ << ' ' << k1 << ' ' << k2 <<std::endl;
            stack.add(product);

            if(requests.contains(product)){
                solution::update_partial_solution(product, stack);
                //check if this is new full solution
                for(const T& el : requests){
                    if(!stack.contains(el)){
                        //early comparison exit
                        goto exit;
                    }
                }
                //keep the shortest full solution
                solution::update_full_solution(stack);

            }exit:

            combine<1>(i, j);
            stack.pop();
        }while(++j <= i);
    }while(j = 0, ++i < n);
}

int main(){

    {//initialization of a stack
        us i = s;
        T a = -1;
        //vector_set tmp;
        while (i >>= 1){
            a ^= (a << i);
            stack.add(a);
        }
        std::cout << "Input signals truth tables\n";
        stack.print();

    }
    solution::initialize();
    std::cout << "Recursion depth:" << MAX_DEPTH << '\n';

    combine<0>(0,0);

    std::cout << "============FULL==RESULTS============" << '\n';
    for(auto i:solution::full_solution){
        std::cout << std::bitset<sizeof(T) * 8>(i) << '\n';
    }
    validate_solution(solution::full_solution, true);

    std::cout << "============PARTIAL==RESULTS============" << '\n';
    for(T i : requests){
        std::cout << "for signal: " << i << '\n';
        for(T j: solution::partial_solutions[i]){
            std::cout << std::bitset<sizeof(T) * 8>(j) <<'\n';
        }
        validate_solution(solution::partial_solutions[i], true);

    }
    std::cout << "total nand cals: " << nand_calls << '\n' << "PRESS ENTER TO EXIT\n" ;
    char a;
    std::cin >> a;
}