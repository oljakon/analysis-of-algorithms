#include "pheromonesmap.hpp"

PheromonesMap::PheromonesMap(const int number): number(number)
{
    matrix = new double*[number];
    for (int i = 0; i < number; i++)
    {
        matrix[i] = new double[number]();
    }
}

PheromonesMap::PheromonesMap(const int number, const double ph):
    number(number)
{
    matrix = new double*[number];
    
    for (int i = 0; i < number; i++)
    {
        matrix[i] = new double[number]();
    }

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            matrix[i][j] = matrix[j][i] = ph;
        }
    }
}

PheromonesMap::~PheromonesMap()
{
    for (int i = 0; i < number; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
 }

int PheromonesMap::get_number() const
{
    return number;
}

int PheromonesMap::get_value(const int i, const int j) const
{
    if (i >= number || j >= number)
    {
        throw logic_error("Index out of range");
    }
    return matrix[i][j];
}

void PheromonesMap::set_value(const int i, const int j, const int value)
{
    matrix[i][j] = matrix[j][i] = value;
}

PheromonesMap& PheromonesMap::operator +=(const PheromonesMap& second)
{
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            matrix[i][j] += second.matrix[i][j];
        }
    }

    return *this;
}

PheromonesMap& PheromonesMap::operator +=(const double value)
{
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            matrix[i][j] += value;
        }
    }

    return *this;
}

PheromonesMap& PheromonesMap::operator *=(const double value)
{
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            matrix[i][j] *= value;
        }
    }
    return *this;
}

std::ostream& operator <<(std::ostream& stream, const PheromonesMap& matrix)
{
    for (int i = 0; i < matrix.number; i++)
    {
        for (int j = 0; j < matrix.number; j++)
        {
            stream << matrix.matrix[i][j] << " ";
        }
        stream << endl;
    }
    return stream;
}
