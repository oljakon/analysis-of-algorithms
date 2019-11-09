#ifndef array_hpp
#define array_hpp

//#include <stdio.h>
#include <iostream>

int* init_array(int array_size);
void fill_array(int* array, int array_size);
void make_array(int* array, int array_size, int flag, int rand_max);
void print_array(int* array, int array_size);

unsigned long long tick();

#endif /* array_hpp */
