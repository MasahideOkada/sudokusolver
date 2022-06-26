#include <iostream>
#include "utils.hpp"
#include "basic_techniques.hpp"

int main(void){
    std::vector<int> grid = {
        0, 0, 0, 0, 0, 0, 9, 0, 0,
        0, 0, 0, 5, 0, 0, 0, 8, 3,
        0, 6, 0, 3, 0, 0, 0, 2, 0,
        0, 3, 0, 0, 0, 0, 4, 0, 7,
        0, 0, 1, 9, 6, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 5, 0, 0,
        0, 0, 7, 1, 0, 0, 8, 0, 0,
        4, 0, 9, 0, 2, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 9, 0, 0, 6 
    };
    show_grid(grid);
    std::vector<int> C(81*9, 1);
    make_candidate_matrix(C, grid);
    show_candidates(C);
    return 0;
}