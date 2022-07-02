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
    //loop for 81 cells
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
    //loop for 81 cells
    for (int idx=0; idx<81; ++idx){
        candidates.clear();
        row = idx / 9;
        col = idx % 9;
        std::cout << "(" << row + 1 << ", " << col + 1 << ") : ";
        //loop for 9 values
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

void count_candidates_in_region(std::vector<int> &counting_matrix,
                                const std::vector<int> &candidate_matrix,
                                int region){
    /*
    make information about how many times each candidate appear in 9 blocks of a region,
    where a region means a group of rows, of columns, or of 3x3 boxes.
    for example, let the region be rows.
    if 6 appears 2 times in a 4th row,
    counting_matrix[3][5] = 2.
    but here we implement it as 1D vector
    */
    
    int cell_idx;
    //region 0 is rows, 1 is columns, and 2 is boxes
    if (region == 0){
        //loop for 9 rows
        for (int i=0; i<9; ++i){
            //loop for 9 values
            for (int n=0; n<9; ++n){
                //loop for 9 cells in a row
                for (int j=0; j<9; ++j){
                    cell_idx = 9 * i + j;
                    counting_matrix[9 * i + n] += candidate_matrix[9 * cell_idx + n];
                }
            }
        }
    }
    if (region == 1){
        //loop for 9 columns
        for (int i=0; i<9; ++i){
            for (int n=0; n<9; ++n){
                //loop for 9 cells in a column
                for (int j=0; j<9; ++j){
                    cell_idx = 9 * j + i;
                    counting_matrix[9 * i + n] += candidate_matrix[9 * cell_idx + n];
                }
            }
        }
    }
    if (region == 2){
        int box_row, box_col;
        int sub_row, sub_col;
        //loop for 9 boxes
        for (int i=0; i<9; ++i){
            box_row = 3 * (i / 3);
            box_col = 3 * (i % 3);
            for (int n=0; n<9; ++n){
                //loop for 9 cells in a box
                for (int j=0; j<9; ++j){
                    sub_row = j / 3;
                    sub_col = j % 3;
                    cell_idx = 9 * (box_row + sub_row) + (box_col + sub_col);
                    counting_matrix[9 * i + n] += candidate_matrix[9 * cell_idx + n];
                }
            }
        }
    }
}

void find_cells(std::vector<int> &cells,
                const std::vector<int> &candidate_matrix,
                const std::vector<int> &vals,
                int region, int block){
    //find which cells in a block of a region has one of the values
    
    //store cells in one hot representation
    std::vector<int> cell_indices(81, 0);
    int cell_idx;
    if (region == 0){
        //loop for 9 cells in a row
        for (int i=0; i<9; ++i){
            cell_idx = 9 * block + i;
            //loop for values
            for (auto v: vals){
                cell_indices[cell_idx] = candidate_matrix[9 * cell_idx + v];
            }
        }
    }
    if (region == 1){
        //loop for 9 cells in a column
        for (int i=0; i<9; ++i){
            cell_idx = 9 * i + block;
            //loop for values
            for (auto v: vals){
                cell_indices[cell_idx] = candidate_matrix[9 * cell_idx + v];
            }
        }
    }
    if (region == 2){
        int box_row = 3 * (block / 3);
        int box_col = 3 * (block % 3);
        int sub_row, sub_col;
        //loop for 9 cells in a box
        for (int i=0; i<9; ++i){
            sub_row = i / 3;
            sub_col = i % 3;
            cell_idx = 9 * (box_row + sub_row) + (box_col + sub_col);
            //loop for values
            for (auto v: vals){
                cell_indices[cell_idx] = candidate_matrix[9 * cell_idx + v];
            }
        }
    }
    //store result
    for (int idx=0; idx<81; ++idx){
        if (cell_indices[idx] == 1){
            cells.push_back(idx);
        }
    }
}

void get_peer_cells(std::vector<int> &peer_cells,
                    const int input_cell_idx){
    //peer cells are cells (20 in total) that exist in the same block as the input cell

    //store peer cells in one hot representation
    std::vector<int> peer_vector(81, 0);
    int row = input_cell_idx / 9;
    int col = input_cell_idx % 9;
    int box_row = 3 * (row / 3);
    int box_col = 3 * (col / 3);
    int sub_row, sub_col;
    int row_peer, col_peer, box_peer;
    //update peer vector
    for (int i=0; i<9; ++i){
        row_peer = 9 * row + i;
        col_peer = 9 * i + col;
        sub_row = i / 3;
        sub_col = i % 3;
        box_peer = 9 * (box_row + sub_row) + (box_col + sub_col);
        peer_vector[row_peer] = 1;
        peer_vector[col_peer] = 1;
        peer_vector[box_peer] = 1;
    }
    //get rid of input cell index from the peer vector
    peer_vector[input_cell_idx] = 0;
    //get indices of peer cells from peer vector
    int peer_count = 0;
    for (int i=0; i<81; ++i){
        if (peer_vector[i] == 1){
            peer_cells[peer_count] = i;
            peer_count += 1;
        }   
    }
}