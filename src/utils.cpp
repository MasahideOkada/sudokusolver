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
    candidate matrix C is a 9x9 matrix to show what a cell has as candidates.
    for example, if cell(2, 4) or cell 13 has 2, 3, adn 6 as candidates, 
    13th row of the matrix is [0, 1, 1, 0, 0, 1, 0, 0, 0].
    but here we implement the matrix as 1D vector. 
    */
    int row, col, box_row, box_col;
    int val1, val2;
    for (int idx=0; idx<81; ++idx){
        //check the value of a cell
        val1 = grid[idx];
        if (val1 != 0){
            /*
            if the cell is already occupied, 
            the value is the only single candidate for the cell.
            */ 
            for (int n=0; n<9; ++n){
                if (n != val1 - 1){
                    candidate_matrix[9 * idx + n] = 0;
                }
            }
        }
        else{
            /*
            if the cell is blank, 
            look at other cells in the same block and find canditates for it.
            */ 
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
    //to store candidates
    std::vector<int> candidates;
    candidates.reserve(9);
    int num_cands;
    for (int idx=0; idx<81; ++idx){
        candidates.clear();
        row = idx / 9;
        col = idx % 9;
        std::cout << "(" << row + 1 << ", " << col + 1 << ") : ";
        for (int n=0; n<9; ++n){
            //store n if n+1 is a candidate
            if (candidate_matrix[9 * idx + n] == 1){
                candidates.push_back(n);
            }
        }
        num_cands = (int)candidates.size();
        //show candidates
        for (int i=0; i<num_cands; ++i){
            if (i != num_cands - 1){
                std::cout << candidates[i] + 1 << ", ";
            }
            else{
                std::cout << candidates[i] + 1;
            }
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
}