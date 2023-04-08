#include <iostream>
#include <vector>
#include <Bitset>
#include "../dev/BitSet.h"
typedef unsigned int ui;

static ui* parent;
static ui* size;
ui areas;

ui get_root (ui v) {
    if (v == parent[v])
        return v;

    return parent[v] = get_root(parent[v]);
}

void union_sets (ui a, ui b) {
    a = get_root(a);
    b = get_root(b);
    if (a != b) {
        --areas;
        if (size[a] < size[b])
            std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

int main(){
    unsigned int M, N;
    ui a,b;
    std::cin >> M >>  N;
    parent = new ui[N];
    size = new ui[N];
    areas = N;
    for(ui i = 0; i < N; ++i){
        parent[i] = i;
        size[i] = 1;
    }

    std::pair<ui,ui>* Edges = new std::pair<ui, ui> [M];

    for(ui i = 0; i < M; ++i){
        std::cin >> a >> b;
        Edges[i] = {a,b};
    }

    ui Q;
    std::cin >> Q;
    BitSet removed(M, true);
    ui *order = new ui[Q];
    ui x;
    for(ui i = 0; i < Q; ++i){
        std::cin >> x;
        order[i] = x;
        removed.set_to(x, false);
    }

    std::pair<ui, ui> edge ;
    for(ui i = 0; i < M; ++i){
        if(removed[i]){
            edge = Edges[i];
            union_sets(edge.first, edge.second);
        }
    }

    ui * ans = new ui[Q] {0};

    for(ui i = Q; i >= 0; --i){
        ans[i] = areas;
        edge = Edges[order[i]];
        union_sets(edge.first, edge.second);
    }

    for(ui i=0; i < Q; ++i){
        std::cout << ans[i] << ' ';
    }
}