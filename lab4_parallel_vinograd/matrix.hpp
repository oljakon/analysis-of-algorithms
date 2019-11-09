#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <iostream>
#include <thread>

class Matrix
{
public:
    Matrix(int n, int m);
    ~Matrix();
    
    Matrix vinograd_mult(const Matrix& mtr1, const Matrix& mtr2);
    Matrix vinograd_mult_parallel(const Matrix &a, const Matrix &b, int count);
    
    void create_matrix(int n, int m);
    void generate_random(int rand_max);
    void print_matrix(int n, int m);
    
    friend void func_thread(const Matrix &a, const Matrix &b, Matrix &res,  int* row_factor,  int* col_factor, int num, int count);
    
private:
    int row;
    int column;
    int** data;
};

#endif /* matrix_hpp */
