#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <iostream>

class Matrix
{
public:
    Matrix(int n, int m);
    ~Matrix();
    
    Matrix classic_mult(const Matrix& mtr1, const Matrix& mtr2);
    Matrix vinograd_mult(const Matrix& mtr1, const Matrix& mtr2);
    Matrix vinograd_mult_optm(const Matrix& mtr1, const Matrix& mtr2);
    
    void create_matrix(int n, int m);
    void generate_random(int rand_max);
    void print_matrix(int n, int m);
    
private:
    int row;
    int column;
    int** data;
};

unsigned long long tick();

#endif /* matrix_hpp */
