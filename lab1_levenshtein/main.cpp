#include "levenshtein.hpp"

using namespace std;

int main(void)
{
    unsigned long long t;
    Levenshtein levenshtein;
    string str1, str2;
    int result = 0;
    int choiсe;

    cout << "Input first string: ";
    getline(cin, str1);
    levenshtein.set_str1(str1);
            
    cout << "Input second string: ";
    getline(cin, str2);
    levenshtein.set_str2(str2);
            
    cout << "\nLevenshtein:" << endl << endl;
    t = tick();
    result = levenshtein.levenshtein();
    t = tick() - t;
    levenshtein.print_matrix();
    cout << "Levenshtein distance: " << result << endl;
    //cout << "Time in ticks:  " << t << endl << endl;
            
    cout << "\nDamerau-Levenshtein:" << endl << endl;
    t = tick();
    result = levenshtein.damerau_levenshtein();
    t = tick() - t;
    levenshtein.print_matrix();
    cout << "Damerau-Levenshtein distance: " << result << endl;
    //cout << "Time in ticks: " << t << endl << endl;
            
    cout << "\nDamerau-Levenshtein recursive: " << endl;
    t = tick();
    result = levenshtein.damerau_levenshtein_recursive(levenshtein.str1_len(), levenshtein.str2_len());
    t = tick() - t;
    cout << "Damerau-Levenshtein recursive distance: " << result << endl << endl;
    //cout << "Time in ticks: " << t << endl << endl;

}
