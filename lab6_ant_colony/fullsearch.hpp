#ifndef fullsearch_hpp
#define fullsearch_hpp

#include <stdio.h>
#include <vector>
#include "citiesmap.hpp"
#include "pheromonesmap.hpp"

static int s(0);

int full_search(const CitiesMap &distance);
void hamilton(const CitiesMap &distance, vector<int> &min_path, int &min_distance, vector<int> &cur_path, vector<bool> &visited, int &cur_len);

#endif /* fullsearch_hpp */
