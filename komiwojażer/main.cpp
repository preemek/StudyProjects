// Przemysław Myśliwiec, 302885

#include <iostream>
#include "tsp.hpp"
#include <cmath>
#define INF (NAN)

int main() {

    std::vector<std::vector<double>> cost_matrix {
            {INF, 12,   3,  45,   6},
            {78, INF,  90,  21,   3},
            { 5,  56, INF,  23,  98},
            {12,   6,   8, INF,  34},
            { 3,  98,   3,   2, INF}
    };

    std::vector<int> results;

    results=tsp(cost_matrix);

    for(int i=0; i<results.size(); i++){
        std::cout<< results[i];
    }

    return 0;
}