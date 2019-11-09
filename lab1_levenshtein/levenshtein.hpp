#ifndef levenshtein_hpp
#define levenshtein_hpp

#include <vector>
#include <iostream>

using namespace std;

class Levenshtein
{
public:
    Levenshtein();
    string get_str1();
    string get_str2();
    
    int str1_len();
    int str2_len();
    
    void set_str1(string new_string);
    void set_str2(string new_string);
    
    int levenshtein();
    int damerau_levenshtein();
    int damerau_levenshtein_recursive(int i, int j);
    
    void init_matrix(int n, int m);
    void print_matrix();
    
private:
    string str1;
    string str2;
    vector <vector<int>> matrix;
};

unsigned long long tick();

#endif /* levenshtein_hpp */
