#ifndef citiesmap_hpp
#define citiesmap_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class CitiesMap
{
    public:
        CitiesMap(const int cities_number);
        CitiesMap(const int cities_number, const int min_distance, const int max_distance);
        CitiesMap(const int cities_number, const int ph);
        ~CitiesMap();
    
        int get_cities_number() const;
        int get_value(const int first, const int second) const;
        void set_value(const int first, const int second, const int value);
    
        CitiesMap& operator +=(const CitiesMap& other);
        CitiesMap& operator +=(const double value);
        CitiesMap& operator *=(const double value);

        friend ostream& operator <<(ostream& stream, const CitiesMap& matrix);

    private:
        const int cities_number;
        int** matrix;
};

#endif /* citiesmap_hpp */
