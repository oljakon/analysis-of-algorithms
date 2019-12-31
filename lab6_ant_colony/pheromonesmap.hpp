#ifndef pheromonesmap_hpp
#define pheromonesmap_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class PheromonesMap
{
    public:
        PheromonesMap(const int cities_number);
        PheromonesMap(const int cities_number, const double ph);
        ~PheromonesMap();
    
        int get_number() const;
        int get_value(const int first, const int second) const;
        void set_value(const int first, const int second, const int value);
    
        PheromonesMap& operator +=(const PheromonesMap& other);
        PheromonesMap& operator +=(const double value);
        PheromonesMap& operator *=(const double value);

        friend ostream& operator <<(ostream& stream, const PheromonesMap& matrix);

    private:
        const int number;
        double** matrix;
};

#endif /* pheromonesmap_hpp */
