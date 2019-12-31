#include "colony.hpp"

using namespace std;

double rand_double(void)
{
    int tmp = rand() % 100;
    return (tmp / 100.0);
}

int ant_colony(const int cities_number, vector<int>& route, const CitiesMap& distance, const double alpha, const double beta, const double Q, const double evaporation, const int max_time)
{
    int length = 0;
    route.clear();
    
    PheromonesMap pheromones(cities_number, 10);
    
    double coin;

    for (int time = 0; time < max_time; time++)
    {
        PheromonesMap ant_pheromones(cities_number, 10);
        
        for (int ant = 0; ant < cities_number; ant++)
        {
            list<int> unvisited_cities;
            int next_city = cities_number;
            int current_len = 0;
            
            int current_city = ant;
    
            for (int j = 0; j < ant; j++)
            {
                unvisited_cities.push_back(j);
            }
            for (int j = ant + 1; j < cities_number; j++)
            {
                unvisited_cities.push_back(j);
            }
            
            vector<int> visited_cities;
            visited_cities.push_back(ant);
            
            while (unvisited_cities.size() > 0)
            {
                double max_probability = 0;

                for (int different_city : unvisited_cities)
                {
                    if (distance.get_value(ant, different_city) != 0)
                    {
                        double full_probability = 0;
                        for (int j : unvisited_cities)
                        {
                            full_probability += pow(pheromones.get_value(ant, j), alpha) *\
                                    pow(1.0 / distance.get_value(ant, j), beta);
                            
                        }
                        
                        double probability = (pow(pheromones.get_value(ant, different_city), alpha) *\
                                pow(1.0 / distance.get_value(ant, different_city), beta)) / full_probability;
                        
                        coin = rand_double();
                        int best_probability = 0;
                        double sum_probability = 0;
                        
                        for (int s = 0; s < cities_number; s++)
                        {
                            sum_probability += probability;
                            if (sum_probability > coin)
                            {
                                max_probability = probability;
                                next_city = different_city;
                                break;
                            }
                        }
                    }
                }
                
                visited_cities.push_back(next_city);
                unvisited_cities.remove(next_city);
                current_len += distance.get_value(current_city, next_city);
                
                current_city = next_city;
            }

            int new_len = current_len + distance.get_value(visited_cities.front(), visited_cities.back());
 
            if (new_len < length || length == 0)
            {
                length = new_len;
                route = visited_cities;
            }

            auto it = visited_cities.cbegin();
            for (auto it2 = it + 1; it2 != visited_cities.cend(); ++it, ++it2)
            {
                ant_pheromones.set_value(*it, *it2, ant_pheromones.get_value(*it, *it2) + Q / current_len);
            }
        }

        pheromones *= (1 - evaporation);
        pheromones += ant_pheromones;
    }
    
    return length;
}
