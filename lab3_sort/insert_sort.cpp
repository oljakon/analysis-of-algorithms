#include "insert_sort.hpp"

void insertion_sort(int* array, int array_size)
{
    int tmp, item;
    for (int i = 1; i < array_size; i++)
    {
        tmp = array[i];
        item = i - 1;
        while (item >= 0 && array[item] > tmp)
        {
            array[item + 1] = array[item];
            array[item] = tmp;
            item--;
        }
    }
}
