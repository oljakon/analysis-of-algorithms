#include <iostream>

#include "KMP.h"
#include "BM.h"

using namespace std;

int main()
{
    char txt[] = "theretheyare";
    char pat[] = "they";
    
    cout << txt << "\n" << pat << endl << endl;
    
    cout << "KMP:" << endl;
    int ind_kmp = kmp_search(pat, txt);
    cout << "Pattern found at index: "  << ind_kmp << endl << endl;
    
    cout << "BM:" << endl;
    int ind_bm = bm_search(txt, pat);
    cout << "Pattern found at index: "  << ind_bm << endl;

    return 0;
}
