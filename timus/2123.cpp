#include <iostream>

typedef int64_t ul;
typedef uint_fast16_t us;

class solution{
public:
    us n;
    ul W;
    ul* items;
    ul* partial_sums;
    ul under_counter;
    ul over_counter;
    ul exact_counter ;
    ul recursion_call_section;
    ul leaf_check;
    solution(){
        std::cin >> n >>  W;
        items = new ul[n];
        partial_sums = new ul[n];
        ul cur_item, cur_sum = 0;
        for(us i = 0; i < n; ++i){
            std::cin >> cur_item;
            items[i] = cur_item;
            cur_sum += 2 * cur_item;
            partial_sums[i] = cur_sum;
        }

        under_counter = 0;
        over_counter = 0;
        exact_counter = 0;
        recursion_call_section = 0;
        leaf_check = 0;
    }

    ul combinations(ul req_sum, us cur_item_idx){
        if(req_sum < 0){
            ++over_counter;
            return 0;
        }
        if(partial_sums[cur_item_idx] < req_sum){
            ++under_counter;
            return 0;
        }
        if(req_sum == 0){
            ++exact_counter;
            return 1;
        }
        if(cur_item_idx){
            ++recursion_call_section;
            return combinations(req_sum, cur_item_idx - 1) + combinations(req_sum - items[cur_item_idx], cur_item_idx - 1) + combinations(req_sum - (items[cur_item_idx] << 1), cur_item_idx - 1);
        }
        ++leaf_check;
        return (req_sum == items[cur_item_idx]) + (req_sum == items[cur_item_idx] << 1);
        /*
        if(req_sum <= 0 || partial_sums[cur_item_idx] < req_sum) return !req_sum;
        //Если сумма <0, то переборщили с предметами, отсекаем ветвь.
        //Если нужно больше чем сумма всех оставшихся, то недобор, можно не пытаться.
        //Если она =0, возвращаем 1, любые дальнейшие добавления испортят сумму.
        if(cur_item_idx) return combinations(req_sum, cur_item_idx - 1) +
                                combinations(req_sum - items[cur_item_idx], cur_item_idx - 1) +
                                combinations(req_sum - (items[cur_item_idx] << 1), cur_item_idx - 1);
        return (req_sum == items[cur_item_idx]) + (req_sum == items[cur_item_idx] << 1);
        */
    }

    ul solve(){
        return combinations(W, n - 1);
    }

    void counters(){
        std::cout << "\nover counted " << over_counter << "  under counted "<< under_counter << "  premature solutions " << exact_counter << "  recursion section " << recursion_call_section << "  leaf touches " << leaf_check << '\n';
    }

};


int main(){
    solution a;
    std::cout << a.solve();
    a.counters();
}