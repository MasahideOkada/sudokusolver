#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <cassert>

void show_grid(const std::vector<int> &grid);

void make_candidate_matrix(std::vector<int> &candidate_matrix,
                           const std::vector<int> &grid);

void show_candidates(const std::vector<int> &candidate_matrix);

void count_candidates_in_region(std::vector<int> &counting_matrix,
                                const std::vector<int> &candidate_matrix,
                                int region);

void find_cells(std::vector<int> &cells,
                const std::vector<int> &candidate_matrix,
                const std::vector<int> &vals,
                int region, int block);

void get_peer_cells(std::vector<int> &peer_cells,
                    const int input_cell_idx);

void get_peer_cells_in_onehot(std::vector<int> &peer_vector,
                              const int input_cell_idx);

void get_common_cells(std::vector<int> &common_cells,
                      const std::vector<int> &input_cells);

#endif