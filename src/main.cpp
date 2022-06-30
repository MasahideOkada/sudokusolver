#include <iostream>
#include "utils.hpp"
#include "basic_techniques.hpp"

int main(void){
    std::vector<int> grid = {
        0, 0, 2, 1, 9, 3, 0, 0, 0,
        0, 0, 0, 0, 0, 7, 0, 0, 0,
        7, 0, 0, 0, 4, 0, 0, 1, 9,
        8, 0, 3, 0, 0, 0, 6, 0, 0,
        0, 4, 5, 0, 0, 0, 2, 3, 0,
        0, 0, 7, 0, 0, 0, 5, 0, 4,
        3, 7, 0, 0, 8, 0, 0, 0, 6,
        0, 0, 0, 6, 0, 0, 0, 0, 0,
        0, 0, 0, 5, 3, 4, 1, 0, 0 
    };
    show_grid(grid);
    std::vector<int> C(81*9, 1);
    make_candidate_matrix(C, grid);
    //show_candidates(C);
    //find_naked_singles(C, grid);
    find_hidden_singles(C, grid);
    show_grid(grid);
    //show_candidates(C);
    return 0;
}