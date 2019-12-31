#ifndef colony_hpp
#define colony_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <vector>
#include <list>
#include "citiesmap.hpp"
#include "pheromonesmap.hpp"

double rand_double(void);

int ant_colony(const int cities_number, vector<int>& route, const CitiesMap& distance,
               const double alpha, const double beta, const double Q, const double evaporation, const int max_time);

#endif /* colony_hpp */
