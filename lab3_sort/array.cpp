#include "array.hpp"

using namespace std;

int* init_array(int array_size)
{
    int* array = new int[array_size];
    
    return array;
}

void fill_array(int* array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        cin >> array[i];
    }
}

void make_array(int* array, int array_size, int flag, int rand_max)
{
    if (flag == 0)
    {
        for (int i = 0; i < array_size; i++)
        {
            array[i] = i;
        }
    }
    
    if (flag == 1)
    {
        int elem = array_size;
        for (unsigned i = 0; i < array_size; ++i, --elem)
        {
            array[i] = elem;
        }
    }
    
    if (flag == 2)
    {
        for (int i = 0; i < array_size; i++)
        {
            array[i] = rand() % rand_max;
        }
    }
}

    
void print_array(int* array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        cout << array[i] << " ";
    }
    cout << std::endl;
}

unsigned long long tick()
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}
