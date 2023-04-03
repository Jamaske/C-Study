#include <iostream>
#include <bitset>

class Graph{
protected:
public:
    const bool directional;

    const uint32_t vertices_number;

};




class Adj_Matrix: Graph{
public:

    std::bitset<vertices_number> Matrix;
};



