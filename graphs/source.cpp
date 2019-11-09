#include <vector>
#include <iostream>
#include <random>

int main(int argc, char *argv[])
{
    std::vector<std::vector<int>> matrix;       // 0
    int p;                                      // 1
    int r = 10;                                 // 2
    int tmp;                                    // 3
    int size = 3;                               // 4

    for (int i = 0; i < size; i++)              // 5
    {
        std::vector<int> row;                   // 6
        for (int j = 0; j < size; j++)          // 7
        {
            p = rand() % r;                     // 8
            row.push_back(p);                   // 9
        }
        matrix.push_back(row);                  // 10
    }

    for (int i = 0; i < size; i++)              // 11
    {
        for (int j = 0; j < i; j++)             // 12
        {
            tmp = matrix[j][i];                 // 13
            matrix[j][i] = matrix[i][j];        // 14
            matrix[i][j] = tmp;                 // 15
        }
    }
    
    return 0;
}

