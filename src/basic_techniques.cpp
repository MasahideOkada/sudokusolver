#include "basic_techniques.hpp"

void find_naked_singles(std::vector<int> &candidate_matrix, 
                        std::vector<int> &grid){
    /*
    A naked single means the only single candidate for a blank cell.
    That means the value can be eliminated from other cells in blocks to which the cell belong.
    */

    //store result in [cell idx, value] format
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
                }
            }
        }
    }
    //show the result and update grid and candidate matrix
    int row, col;
    std::vector<int> peer_cells(20);
    if (count_result == 0){
        std::cout << "No naked singles\n";
    }
    else{
        std::cout << "Naked singles found\n";
        for (int c=0; c<count_result; ++c){
            idx = all_results[c][0];
            val = all_results[c][1];
            row = idx / 9;
            col = idx % 9;
            std::cout << "(" << row + 1 << ", " << col + 1 << "): " << val + 1 << "\n";
            //update the grid
            grid[idx] = val + 1;
            //update the candidate matrix
            get_peer_cells(peer_cells, idx);
            for (auto peer_idx: peer_cells){
                candidate_matrix[9 * peer_idx + val] = 0;
            }
        }
    }
    std::cout << std::flush;
}

void find_hidden_singles(std::vector<int> &candidate_matrix,
                         std::vector<int> &grid){
    /*
    A hidden single is a candidate(value) that appears in only one blank cell in a block.
    That means other values can be eliminated from the cell.
    */

    //store results in [cell idx, value] format
    std::vector<int> result;
    std::vector<std::vector<int>> all_results;
    result.resize(2);
    all_results.reserve(81);
    int count_result = 0;
    int idx, val;

    std::vector<int> counting_matrix(81, 0);
    std::vector<int> cells;
    std::vector<int> vals(1, 0);
    int num_cands;
    //region 0 is rows, 1 is columns, and 2 is boxes
    for (int region=0; region<3; ++region){
        //count how many times a candidate appears in a region
        std::fill(counting_matrix.begin(), counting_matrix.end(), 0);
        count_candidates_in_region(counting_matrix, candidate_matrix, region);
        
        //loop for 9 blocks
        for (int block=0; block<9; ++block){
            //loop for 9 values
            for (int v=0; v<9; ++v){
                cells.clear();
                num_cands = 0;
                //check if the value appears only once
                if (counting_matrix[9 * block + v] == 1){
                    vals[0] = v;
                    //find a cell that has the value
                    find_cells(cells, candidate_matrix, vals, region, block);
                    idx = cells[0];
                    val = v;
                    //get the number of candidates in the cell
                    for (int n=0; n<9; ++n){
                        num_cands += candidate_matrix[9 * idx + n];
                    }
                    //if the cell has more than one candidate, store the result
                    if (num_cands > 1){
                        result[0] = idx;
                        result[1] = val;
                        all_results.push_back(result);
                        count_result += 1;
                    }
                }
            }
        }
    }
    //show the results
    int row, col;
    if (count_result == 0){
        std::cout << "No hidden singles\n";
    }
    else{
        std::cout << "Hidden singles found\n";
        for (int c=0; c<count_result; ++c){
            idx = all_results[c][0];
            val = all_results[c][1];
            row = idx / 9;
            col = idx % 9;
            std::cout << "(" << row + 1 << ", " << col + 1 << "): " << val + 1 << "\n";
            //update the grid
            grid[idx] = val + 1;
            //update the candidate matrix
            for (int v=0; v<9; ++v){
                if (v != val){
                    candidate_matrix[9 * idx + v] = 0;
                }
            }            
        }
    }
    std::cout << std::flush;
}

void find_naked_tuples(std::vector<int> &candidate_matrix){
    /* 
    When a group of N cells in a block has only N candidates in total, their candidates are a naked tuple.
    That means those values can be eliminated from other cells in the block.
    */

}