#include <chrono>
#include "matrix.hpp"

using namespace std;
using namespace chrono;

int main()
{
    int choice = -1;
    while (choice != 0)
    {
        cout << "1. Multiply matrices" <<
                "\n2. Testing time" <<
                "\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int n1, m1, n2, m2;
            cout << "\nInput number of rows of first matrix: ";
            cin >> n1;
            cout << "Input number of columns of first matrix: ";
            cin >> m1;
            

            Matrix mtr1(n1, m1);
            mtr1.create_matrix(n1, m1);
            mtr1.print_matrix(n1, m1);
                
            cout << "\nInput number of rows of second matrix: ";
            cin >> n2;
            cout << "Input number of columns of second matrix: ";
            cin >> m2;
         
            Matrix mtr2(n2, m2);;
            mtr2.create_matrix(n2, m2);
            mtr2.print_matrix(n2, m2);
            
            cout << "\nClassic Vinograd: " << endl;
            Matrix res1 = res1.vinograd_mult(mtr1, mtr2);
            res1.print_matrix(2, 2);
            cout << "\nParallel Vinograd: " << endl;
            Matrix res2 = res2.vinograd_mult_parallel(mtr1, mtr2, 3);
            res2.print_matrix(2, 2);
                
            break;
        }

        case 2:
        {
            int threads = 16;
            int top_random = 100;
            int tests_number = 10;
            
            auto start = high_resolution_clock::now(),
                stop = high_resolution_clock::now();
            int buf = 0;
                
            for (int size = 100; size <= 1000; size += 100)
            {
                cout << "\nSize: " << size;
                
                Matrix mtr1(size, size);
                Matrix mtr2(size, size);
        
                mtr1.generate_random(top_random);
                mtr2.generate_random(top_random);
                
                cout << "\nClassic Vinograd: ";
                for (int k = 0; k < tests_number; ++k)
                {
                    start = high_resolution_clock::now();
                    mtr1.vinograd_mult(mtr1, mtr2);
                    stop = high_resolution_clock::now();
                    auto ms = duration_cast<microseconds>(stop - start).count();
                    buf += ms;
                }
                cout << buf / tests_number << " ticks" << endl;
                buf = 0;
                
                for (int j = 1; j <= threads; j *= 2)
                {
                    cout << "\nThreads: " << j << endl;
                    cout << "Parallel Vinograd: ";
                    for (int k = 0; k < tests_number; ++k)
                    {
                        start = high_resolution_clock::now();
                        mtr1.vinograd_mult_parallel(mtr1, mtr2, threads);
                        stop = high_resolution_clock::now();
                        auto ms = duration_cast<microseconds>(stop - start).count();
                        buf += ms;
                    }
                    cout << buf / tests_number << " ticks" << endl;
                    buf = 0;
                }
            }
            
            for (int size = 101; size <= 1001; size += 100)
                {
                    cout << "\nSize: " << size;
                    
                    Matrix mtr1(size, size);
                    Matrix mtr2(size, size);
            
                    mtr1.generate_random(top_random);
                    mtr2.generate_random(top_random);
                    
                    cout << "\nClassic Vinograd: ";
                    for (int k = 0; k < tests_number; ++k)
                    {
                        start = high_resolution_clock::now();
                        mtr1.vinograd_mult(mtr1, mtr2);
                        stop = high_resolution_clock::now();
                        auto ms = duration_cast<microseconds>(stop - start).count();
                        buf += ms;
                    }
                    cout << buf / tests_number << " ticks" << endl;
                    buf = 0;
                    
                    for (int j = 1; j <= threads; j *= 2)
                    {
                        cout << "\nThreads: " << j << endl;
                        cout << "Parallel Vinograd: ";
                        for (int k = 0; k < tests_number; ++k)
                        {
                            start = high_resolution_clock::now();
                            mtr1.vinograd_mult_parallel(mtr1, mtr2, threads);
                            stop = high_resolution_clock::now();
                            auto ms = duration_cast<microseconds>(stop - start).count();
                            buf += ms;
                        }
                        cout << buf / tests_number << " ticks" << endl;
                        buf = 0;
                    }
                }
                
            break;
        }
        }
    }
}
