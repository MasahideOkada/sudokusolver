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