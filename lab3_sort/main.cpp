#include "array.hpp"
#include "insert_sort.hpp"
#include "bubble_sort.hpp"
#include "selection_sort.hpp"

using namespace std;

int main()
{
    unsigned  long long t;
    int choice = -1;
    while (choice != 0)
    {
        cout << "1. Sort array" <<
                "\n2. Testing time" <<
                "\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int len;
            cout << "Input array lenght: ";
            cin >> len;
            if (len <= 0)
            {
                cout << "Incorrect size" << endl;
                break;
            }
                
            cout << "Enter int numbers separated by spaces: ";
            int *array = init_array(len);
            fill_array(array, len);
            
            cout << "Insertion sort: ";
            t = tick();
            insertion_sort(array, len);
            t = tick() - t;
            cout << t << endl;
            print_array(array, len);
            
            cout << "Bubble sort: ";
            bubble_sort(array, len);
            print_array(array, len);
            
            cout << "Selection sort: ";
            selection_sort(array, len);
            print_array(array, len);
                
            break;
        }

        case 2:
        {
            unsigned  long long t, buf = 0;
            int top_random = 100;
            int tests_number = 10;
            
            for (int size = 100; size <= 1000; size += 100)
            {
                cout << "\nSize: " << size << endl;
                int *array = init_array(size);
                
                cout << "\nInsertion sort: " << endl;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 0, top_random);
                    t = tick();
                    insertion_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Best: " << buf / tests_number << " ticks" << endl;
                buf = 0;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 1, top_random);
                    t = tick();
                    insertion_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Worst: " << buf / tests_number << " ticks" << endl;
                buf = 0;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 2, top_random);
                    t = tick();
                    insertion_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Random: " << buf / tests_number << " ticks" << endl;
                buf = 0;
                cout << "\nBubble sort: " << endl;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 0, top_random);
                    t = tick();
                    bubble_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Best: " << buf / tests_number << " ticks" << endl;
                buf = 0;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 1, top_random);
                    t = tick();
                    bubble_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Worst: " << buf / tests_number << " ticks" << endl;
                buf = 0;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 2, top_random);
                    t = tick();
                    bubble_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Random: " << buf / tests_number << " ticks" << endl;
                buf = 0;
                cout << "\nSelection sort: " << endl;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 0, top_random);
                    t = tick();
                    selection_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Best: " << buf / tests_number << " ticks" << endl;
                buf = 0;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 1, top_random);
                    t = tick();
                    selection_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Worst: " << buf / tests_number << " ticks" << endl;
                buf = 0;
                for (int i = 0; i < tests_number; ++i)
                {
                    make_array(array, size, 2, top_random);
                    t = tick();
                    selection_sort(array, size);
                    t = tick() - t;
                    buf += t;
                }
                cout << "Random: " << buf / tests_number << " ticks" << endl;
            }
            break;
        }
        }
    }
}
