#include "levenshtein.hpp"

Levenshtein::Levenshtein()
{
    str1 = "";
    str2 = "";
}

string Levenshtein::get_str1()
{
    return this->str1;
}

string Levenshtein::get_str2()
{
    return this->str2;
}

int Levenshtein::str1_len()
{
    return (this->str1).length();
}

int Levenshtein::str2_len()
{
    return (this->str2).length();
}

void Levenshtein::set_str1(string new_string)
{
    this->str1 = new_string;
}

void Levenshtein::set_str2(string new_string)
{
    this->str2 = new_string;
}

void Levenshtein::init_matrix(int n, int m)
{
    for (int i = 0; i < n + 1; i++)
    {
        vector<int> new_line;
        for (int j = 0; j < m + 1; j++)
            new_line.push_back(j);
        new_line[0] = i;
        matrix.push_back(new_line);
    }
}

void Levenshtein::print_matrix()
{
    cout << "  - ";
    for (int i = 0; i < str2_len(); i++)
        cout << str2[i] << " ";
    cout << endl;
    
    for (int i = 0; i < matrix.size(); i++)
    {
        if (i)
            cout << str1[i - 1] << " ";
        else
            cout << "- ";
        for (int j = 0; j < matrix[0].size(); j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

int Levenshtein::levenshtein()
{
    matrix.clear();
    int n = str1.size();
    int m = str2.size();
    init_matrix(n, m);
    
    int cost;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            cost = str1[i - 1] == str2[j - 1] ? 0 : 1;
            matrix[i][j] = min(min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1), matrix[i - 1][j - 1] + cost);
        }
    }

    return matrix[n][m];
}

int Levenshtein::damerau_levenshtein()
{
    matrix.clear();
    int n = str1.size();
    int m = str2.size();
    init_matrix(n, m);
    
    int cost, transp;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            cost = str1[i - 1] == str2[j - 1] ? 0 : 1;
            if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1])
            {
                transp = matrix[i - 2][j - 2] + 1;
                matrix[i][j] = min(min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1), min(matrix[i - 1][j - 1] + cost, transp));
            }
            
            else
            {
                matrix[i][j] = min(min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1), matrix[i - 1][j - 1] + cost);
            }
        }
    }

    return matrix[n][m];
}

int Levenshtein::damerau_levenshtein_recursive(int i, int j)
{
    if (!i)
        return j;
    if (!j)
        return i;
    
    int res, cost;
    
    cost = str1[i - 1] == str2[j - 1] ? 0 : 1;
    
    res = min(min(damerau_levenshtein_recursive(i - 1, j) + 1, damerau_levenshtein_recursive(i, j - 1) + 1), damerau_levenshtein_recursive(i - 1, j - 1) + cost);
    
    if (i > 1 and j >= 1 and str1[i - 1] == str2[j - 2] and str2[i - 1] == str1[j - 1])
    {
        res = min(res, damerau_levenshtein_recursive(i - 2, j - 2) + cost);
    }
    
    return res;
}

unsigned long long tick()
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}
