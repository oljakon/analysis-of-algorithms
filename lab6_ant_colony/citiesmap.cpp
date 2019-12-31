#include "citiesmap.hpp"

CitiesMap::CitiesMap(const int cities_number): cities_number(cities_number)
{
    matrix = new int*[cities_number];
    for (int i = 0; i < cities_number; i++)
    {
        matrix[i] = new int[cities_number]();
    }
}

CitiesMap::CitiesMap(const int cities_number, const int min_distance, const int max_distance):
    cities_number(cities_number)
{
    matrix = new int*[cities_number];
    
    for (int i = 0; i < cities_number; i++)
    {
        matrix[i] = new int[cities_number]();
    }

    const int dist = max_distance - min_distance;
    for (int i = 0; i < cities_number; i++)
    {
        for (int j = i + 1; j < cities_number; j++)
        {
            matrix[i][j] = matrix[j][i] = min_distance + rand() % max_distance;
        }
    }
}

CitiesMap::CitiesMap(const int cities_number, const int ph):
    cities_number(cities_number)
{
    matrix = new int*[cities_number];
    
    for (int i = 0; i < cities_number; i++)
    {
        matrix[i] = new int[cities_number]();
    }

    for (int i = 0; i < cities_number; i++)
    {
        for (int j = i + 1; j < cities_number; j++)
        {
            matrix[i][j] = matrix[j][i] = ph;
        }
    }
}

CitiesMap::~CitiesMap()
{
    for (int i = 0; i < cities_number; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
 }

int CitiesMap::get_cities_number() const
{
    return cities_number;
}

int CitiesMap::get_value(const int i, const int j) const
{
    if (i >= cities_number || j >= cities_number)
    {
        throw logic_error("Index out of range");
    }
    return matrix[i][j];
}

void CitiesMap::set_value(const int i, const int j, const int value)
{
    matrix[i][j] = matrix[j][i] = value;
}

CitiesMap& CitiesMap::operator +=(const CitiesMap& second)
{
    for (int i = 0; i < cities_number; i++)
    {
        for (int j = 0; j < cities_number; j++)
        {
            matrix[i][j] += second.matrix[i][j];
        }
    }

    return *this;
}

CitiesMap& CitiesMap::operator +=(const double value)
{
    for (int i = 0; i < cities_number; i++)
    {
        for (int j = 0; j < cities_number; j++)
        {
            matrix[i][j] += value;
        }
    }

    return *this;
}

CitiesMap& CitiesMap::operator *=(const double value)
{
    for (int i = 0; i < cities_number; i++)
    {
        for (int j = 0; j < cities_number; j++)
        {
            matrix[i][j] *= value;
        }
    }
    return *this;
}

std::ostream& operator <<(std::ostream& stream, const CitiesMap& matrix)
{
    stream << "  | 0 1 2 3 4 5" << "\n" << "-----------------" << std::endl;
    
    for (int i = 0; i < matrix.cities_number; i++)
    {
        stream << i << " | ";
        for (int j = 0; j < matrix.cities_number; j++)
        {
            stream << matrix.matrix[i][j] << " ";
        }
        stream << std::endl;
    }
    return stream;
}
