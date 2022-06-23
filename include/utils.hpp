#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

void show_grid(const std::vector<int> &grid);

void make_candidate_matrix(std::vector<int> &candidate_matrix,
                           const std::vector<int> &grid);

void show_candidates(const std::vector<int> &candidate_matrix);

#endif