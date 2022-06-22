#include "utils.hpp"

//show grid in terminal
void show_grid(const std::vector<int> &grid){
    for (int i=0; i<9; ++i){
        for (int j=0; j<9; ++j){
            //i for i th row, j for j th column
            int idx = i * 9 + j;
            std::cout << grid[idx] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
};

void make_candidate_matrix(std::vector<int> &candidate_matrix,
                           const std::vector<int> &grid){
    /*
    candidate matrix C is 81*9 x 1 matrix to show what a cell has as candidates
    for example, if cell(2, 4) has 6 as a candidate, 
    C[9*(9*2+4) + 5] = 1, otherwise 0
    */
    
};