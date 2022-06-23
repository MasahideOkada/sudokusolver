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
    std::cout << std::flush;
};

void make_candidate_matrix(std::vector<int> &candidate_matrix,
                           const std::vector<int> &grid){
    /*
    candidate matrix C is 81*9 x 1 matrix to show what a cell has as candidates
    for example, if cell(2, 4) has 6 as a candidate, 
    C[9*(9*2+4) + 5] = 1, otherwise 0
    */
    int row, col, box_row, box_col;
    int val1, val2;
    for (int idx=0; idx<81; ++idx){
        val1 = grid[idx];
        if (val1 != 0){
            for (int n=0; n<9; ++n){
                if (n != val1 - 1){
                    candidate_matrix[9 * idx + n] = 0;
                }
            }
        }
        else{
            row = idx / 9;
            col = idx % 9;
            box_row = 3 * (row / 3);
            box_col = 3 * (col / 3);
            //check the values of other cells in the same block
            for (int i=0; i<9; ++i){
                //check same row
                val2 = grid[9 * row + i];
                if (val2 != 0){
                    candidate_matrix[9 * idx + (val2 - 1)] = 0;
                }
                //check same column
                val2 = grid[9 * i + col];
                if (val2 != 0){
                    candidate_matrix[9 * idx + (val2 - 1)] = 0;
                }
                //check same box
                int sub_row = i / 3;
                int sub_col = i % 3;
                val2 = grid[9 * (box_row + sub_row) + (box_col + sub_col)];
                if (val2 != 0){
                    candidate_matrix[9 * idx + (val2 - 1)] = 0;
                }
            }
        }
    }
};

void show_candidates(const std::vector<int> &candidate_matrix){
    int row, col;
    for (int idx=0; idx<81; ++idx){
        row = idx / 9;
        col = idx % 9;
        std::cout << "(" << row + 1 << ", " << col + 1 << ") : ";
        for (int n=0; n<9; ++n){
            if (candidate_matrix[9 * idx + n] == 1){
                std::cout << n + 1 << ", ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
}