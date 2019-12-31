#ifndef kmp_h
#define kmp_h

#include <string>
#include <vector>

using namespace std;

void compute_prefix(char* pat, int M, int* lps);

int kmp_search(char* pat, char* txt)
{
    int M = (int)strlen(pat);
    int N = (int)strlen(txt);

    int result = -1;

    // для самого длинного префикса
    int lps[M];

    compute_prefix(pat, M, lps);

    int i = 0; // индекс txt[]
    int j = 0; // индекс pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            result = i-j;
            j = lps[j - 1];
        }

        // несовпадение
        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return result;
}

// заполняет префикс pat[0..M-1]
void compute_prefix(char* pat, int M, int* lps)
{
    // длина прощлого самого длинного префикса
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // префикс for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

#endif /* kmp_h */
