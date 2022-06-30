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

#endif