#include <iostream>

typedef uint64_t ul;
typedef uint_fast16_t us;

class solution{
public:
    us n;
    ul W;
    ul* items;
    ul* partial_sums;
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
    }

    ul combinations(ul req_sum, us cur_item_idx){

        if(req_sum <= 0 || partial_sums[cur_item_idx] < req_sum) return !req_sum;
        //Если сумма <0, то переборщили с предметами, отсекаем ветвь.
        //Если нужно больше чем сумма всех оставшихся, то недобор, можно не пытаться.
        //Если она =0, возвращаем 1, любые дальнейшие добавления испортят сумму.
        if(cur_item_idx) return combinations(req_sum, cur_item_idx - 1) +
                                combinations(req_sum - items[cur_item_idx], cur_item_idx - 1) +
                                combinations(req_sum - (items[cur_item_idx] << 1), cur_item_idx - 1);
        return (req_sum == items[cur_item_idx]) + (req_sum == items[cur_item_idx] << 1);

    }

    ul solve(){
        return combinations(W, n - 1);
    }

};


int main(){
    solution a;
    std::cout << a.solve();
}