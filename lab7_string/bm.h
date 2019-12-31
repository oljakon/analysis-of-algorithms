#ifndef bm_h
#define bm_h

#include <string>
#include <vector>

# include <limits.h>
# include <string.h>
# include <stdio.h>

# define NO_OF_CHARS 256

int max (int a, int b) { return (a > b)? a: b; }

void badchars(char *str, int size,
                        int badchar[NO_OF_CHARS]);

// Функция поиска по шаблону, использующая эвристику плохого характера алгоритма Бойера-Мура
int bm_search(char *txt,  char *pat)
{
    int m = (int) strlen(pat);
    int n = (int) strlen(txt);

    int result;

    int badchar[NO_OF_CHARS];

    //Заполнение массива плохих символов, вызвав функцию предварительной обработки bad_char_heuristic() для данного шаблона
    badchars(pat, m, badchar);

    int s = 0;  // s - смещение шаблона относительно текста
    while (s <= (n - m))
    {
        int j = m - 1;

        // пока совпадают
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            result = s;
            
            // сдвиг
            // s + m < n на случай, если паттерн появляется в конце текста
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

        }
        else
            s += max(1, j - badchar[txt[s + j]]);
    }

    return result;
}

// Функция предварительной обработки для плохого характера Бойера Мура
void badchars(char *str, int size,
                       int badchar[NO_OF_CHARS])
{
    int i;

    // Инициализировать все вхождения как -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Заполнение фактического значения последнего вхождения символа
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

#endif /* bm_h */
