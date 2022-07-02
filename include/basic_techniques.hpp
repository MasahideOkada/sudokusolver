#ifndef BASIC_TECHNIQUES_HPP
#define BASIC_TECHNIQUES_HPP

#include <iostream>
#include <vector>
#include "utils.hpp"

void find_naked_singles(std::vector<int> &candidate_matrix, 
                        std::vector<int> &grid);

void find_hidden_singles(std::vector<int> &candidate_matrix,
                         std::vector<int> &grid);

void find_naked_tuples(std::vector<int> &candidate_matrix);

#endif