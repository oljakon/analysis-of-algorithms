#include "selection_sort.hpp"

void selection_sort(int* array, int array_size)
{
    int min, tmp;
    for (int i = 0; i < array_size - 1; i++)
    {
      min = i;
      for (int j = i + 1; j < array_size; j++)
      {
        if (array[j] < array[min])
          min = j;
      }
      tmp = array[i];
      array[i] = array[min];
      array[min] = tmp;
    }
}
