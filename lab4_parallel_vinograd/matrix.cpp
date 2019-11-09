#include "matrix.hpp"

Matrix::Matrix(int n, int m)
{
    row = n;
    column = m;
    data = new int*[n];
    for (int i = 0; i < n; i++)
    {
        data[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            data[i][j] = 0;
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < row; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::generate_random(int rand_max)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            data[i][j] = rand() % rand_max;
        }
    }
}

void Matrix::create_matrix(int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << "matrix["<<i<<"]["<<j<<"] = ";
            std::cin >> data[i][j];
        }
    }
}

void Matrix::print_matrix(int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::vinograd_mult(const Matrix &mtr1, const Matrix &mtr2)
{
    Matrix res(mtr1.row, mtr2.column);

    int row_factor[mtr1.row];
    int col_factor[mtr2.column];

    for(int i = 0; i < mtr1.row; i++)
    {
        row_factor[i] = 0;
        for(int j = 0; j < mtr1.column / 2; j++)
        {
            row_factor[i] = row_factor[i] + mtr1.data[i][2 * j] * mtr1.data[i][2 * j + 1];
        }
    }

    for(int i = 0; i < mtr2.column; i++)
    {
        col_factor[i] = 0;
        for(int j = 0; j < mtr2.row / 2; j++)
        {
            col_factor[i] = col_factor[i] + mtr2.data[2 * j][i] * mtr2.data[2 * j + 1][i];
        }
    }

    for(int i = 0; i < mtr1.row; i++)
    {
        for(int j = 0; j < mtr2.column; j++)
        {
            res.data[i][j] = -row_factor[i] - col_factor[j];
            for(int k = 0; k < mtr1.column / 2; k++)
            {
                res.data[i][j] = res.data[i][j] +
                                    (mtr1.data[i][2 * k + 1] + mtr2.data[2 * k][j]) *
                                    (mtr1.data[i][2 * k] + mtr2.data[2 * k + 1][j]);
            }
        }
    }
    
    if(mtr1.column % 2)
    {
        for(int i = 0; i < mtr1.row; i++)
            for(int j = 0; j < mtr2.column; j++)
                res.data[i][j] = res.data[i][j] + mtr1.data[i][mtr1.column - 1] * mtr2.data[mtr1.column - 1][j];
    }

    return res;
}

void func_thread(const Matrix &mtr1, const Matrix &mtr2, Matrix &res,  int* row_factor,  int* col_factor, int num, int count)
{
    for(int i = num; i < mtr1.row; i += count)
    {
        for(int j = 0; j < mtr2.column; j++)
        {
            res.data[i][j] = -row_factor[i] - col_factor[j];
            for(int k = 0; k < mtr1.column / 2; k++)
            {
                res.data[i][j] = res.data[i][j] + (mtr1.data[i][2*k+1] + mtr2.data[2*k][j]) *
                        (mtr1.data[i][2*k] + mtr2.data[2*k+1][j]);
            }
        }
    }
}

Matrix Matrix::vinograd_mult_parallel(const Matrix &mtr1, const Matrix &mtr2, int count)
{
    Matrix res(mtr1.row, mtr2.column);

    int row_factor[mtr1.row];
    int col_factor[mtr2.column];

    for(int i = 0; i < mtr1.row; i++)
    {
        row_factor[i] = 0;
        for(int j = 0; j < mtr1.column / 2; j++)
        {
            row_factor[i] = row_factor[i] + mtr1.data[i][2 * j + 1] * mtr1.data[i][2 * j];
        }
    }

    for(int i = 0; i < mtr2.column; i++)
    {
        col_factor[i] = 0;
        for(int j = 0; j < mtr1.column / 2; j++)
        {
            col_factor[i] = col_factor[i] + mtr2.data[2 * j + 1][i] * mtr2.data[2 * j][i];
        }
    }

    std::thread threads[count];

    for(int i = 0; i < count; i++)
    {
        threads[i] = std::thread(&func_thread, std::ref(mtr1), std::ref(mtr2), std::ref(res), &row_factor[0], &col_factor[0], i, count);
    }
    for(int i = 0; i < count; i++)
    {
        if(threads[i].joinable())
        {
            threads[i].join();
        }
    }


    if(mtr1.column % 2 == 1)
    {
        for(int i = 0; i < mtr1.row; i++)
            for(int j = 0; j < mtr2.column; j++)
                res.data[i][j] = res.data[i][j] + mtr1.data[i][mtr1.column - 1] * mtr2.data[mtr1.column - 1][j];
    }

    return res;
}
