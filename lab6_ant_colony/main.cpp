#include <vector>
#include <iostream>
#include <math.h>
#include <chrono>
#include "citiesmap.hpp"
#include "colony.hpp"
#include "fullsearch.hpp"

using namespace std;
using namespace chrono;

int main()
{
    int cities_number = 5;

    double alpha = 0.5;
    double beta = 0.5;
    double evaporation = 0.5;
    double Q = 10;
    int max_time = 300;
    
    auto start = high_resolution_clock::now(), stop = high_resolution_clock::now();

    CitiesMap distance(cities_number, 1, 9);
    
    cout << distance << endl;
    
    vector<int> route;
    
    start = high_resolution_clock::now();
    const int result = ant_colony(cities_number, route, distance, alpha, beta, Q, evaporation, max_time);
    stop = high_resolution_clock::now();
    auto ms = duration_cast<microseconds>(stop - start).count();
    start = high_resolution_clock::now();
    const int result_full = full_search(distance);
    stop = high_resolution_clock::now();
    auto ms1 = duration_cast<microseconds>(stop - start).count();
    double dif = double(result_full)/double(result);
    cout << "\nACO: " << result << "\nFull search: " << result_full << endl;
    
    /*for (int i = 2; i <= 10; i++)
    {
        CitiesMap distance(i, 1, 10);
        start = high_resolution_clock::now();
        const int result = full_search(distance);
        stop = high_resolution_clock::now();
        auto ms = duration_cast<microseconds>(stop - start).count();
        printf("(%d,%d)\n", i, ms);
    }*/
    
    /*for(float po = 0; po <= 1.00; po += 0.1)
    {
        for (float i = 0; i <= 1.00; i += 0.1)
        {
            for (int tmax = 0; tmax <= 200; tmax += 10)
            {
                start = high_resolution_clock::now();
                const int result = ant_colony(cities_number, route, distance, i, 1-i, Q, po, tmax);
                stop = high_resolution_clock::now();
                auto ms = duration_cast<microseconds>(stop - start).count();
                start = high_resolution_clock::now();
                const int result_full = full_search(distance);
                stop = high_resolution_clock::now();
                auto ms1 = duration_cast<microseconds>(stop - start).count();
                double dif = double(result_full)/double(result);
                printf("%1.2f & %1.2f & %3d & %1.4f \\\\", po, i, tmax, dif);
                cout << endl;
            }
        }
    }*/

    return 0;
}
