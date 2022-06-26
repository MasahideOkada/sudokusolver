#include "basic_techniques.hpp"

void find_naked_candidates(const std::vector<int> &candidate_matrix, 
                           std::vector<int> &grid){
    //the naked candidate means the only single candidate for a blank cell

    //store result in [cell idx, cell value] format
    std::vector<int> result;
    std::vector<std::vector<int>> all_results;
    result.resize(2);
    all_results.reserve(81);
    int count_result = 0;
    //index and value for each cell
    int idx, val;
    int num_cands = 0;
    for (int i=0; i<9; ++i){
        for (int j=0; j<9; ++j){
            idx = 9 * i + j;
            //check the number of candidates for a cell
            num_cands = 0;
            for (int n=0; n<9; ++n){
                num_cands += candidate_matrix[9 * idx + n];
            }
            if (num_cands == 1){
                //if the cell has only one candidate, check the value
                for (int n=0; n<9; ++n){
                    if (candidate_matrix[9 * idx + n] == 1){
                        val = n;
                    }
                }
                //if the cell is blank, store the result
                if (grid[idx] == 0){
                    result[0] = idx;
                    result[1] = val;
                    all_results.push_back(result);
                    count_result += 1;
                    //update the grid
                    grid[idx] = val + 1;
                }
            }
        }
    }
    //show the result
    int row, col;
    if (count_result == 0){
        std::cout << "No naked candidates\n";
    }
    else{
        std::cout << "Naked candidates found\n";
        for (int c=0; c<count_result; ++c){
            idx = all_results[c][0];
            val = all_results[c][1];
            row = idx / 9;
            col = idx % 9;
            std::cout << "(" << row + 1 << ", " << col + 1 << "): " << val + 1 << "\n";
        }
    }
    std::cout << std::flush;
}