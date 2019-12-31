#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;

struct object_type
{
    int index;
    int itemindex;
    time_t time;
    string str = " time is ";
};

vector<object_type> input_objects, output_objects;
queue <object_type> queue1, queue2, queue3;
mutex mtx1, mtx2, mtx3, resmtx;

void fill_objects(int num_of_objects)
{
    for (int i = 0; i < num_of_objects; i++)
    {
        object_type obj;
        time_t t;
        time(&t);
        obj.time = t;
        obj.itemindex = i;
        input_objects.push_back(obj);
    }
    object_type obj;
    time_t t;
    time(&t);
    obj.time = t;
    obj.itemindex = -1;
    input_objects.push_back(obj);
}

void first_line(void)
{
    bool finish = false;
    while (!finish)
    {
        mtx1.lock();
        if(!queue1.empty())
        {
            object_type obj = queue1.front();
            if (obj.itemindex != -1)
            {
                time(&obj.time);
                obj.index = 1;
                obj.str = " == start: ";
                resmtx.lock();
                output_objects.push_back(obj);
                resmtx.unlock();
                queue1.pop();
                
                sleep(1);
                
                mtx2.lock();
                queue2.push(obj);
                mtx2.unlock();
                obj.str = " == end: ";
                resmtx.lock();
                output_objects.push_back(obj);
                resmtx.unlock();
            }
            
            else
            {
                mtx2.lock();
                queue2.push(obj);
                mtx2.unlock();
                finish = true;
            }
        }
        mtx1.unlock();
    }
}

void second_line(void)
{
    bool finish = false;
    while (!finish)
    {
        mtx2.lock();
        if (!queue2.empty())
        {
            object_type obj = queue2.front();
            if (obj.itemindex != -1)
            {
                time(&obj.time);
                obj.index = 2;
                obj.str = " == start: ";
                resmtx.lock();
                output_objects.push_back(obj);
                resmtx.unlock();
                queue2.pop();
                sleep(1);
                mtx3.lock();
                queue3.push(obj);
                mtx3.unlock();
                obj.str = " == end: ";
                resmtx.lock();
                output_objects.push_back(obj);
                resmtx.unlock();
            }
            else
            {
                mtx3.lock();
                queue3.push(obj);
                mtx3.unlock();
                finish = true;
            }
        }
        mtx2.unlock();
    }
}

void third_line(void)
{
    bool finish = false;
    while (!finish)
    {
        mtx3.lock();
        if (!queue3.empty())
        {
            object_type obj = queue3.front();
            if (obj.itemindex != -1)
            {
                time(&obj.time);
                obj.index = 3;
                obj.str = " == start: ";
                resmtx.lock();
                output_objects.push_back(obj);
                resmtx.unlock();
                queue3.pop();
                sleep(1);
                obj.str = " == end: ";
                resmtx.lock();
                output_objects.push_back(obj);
                resmtx.unlock();
            }
            else
            {
                finish = true;
            }

        }
        mtx3.unlock();
    }
}

void sort_log()
{
    object_type tmp;
    for (int i = 0; i < output_objects.size() - 1; i++)
    {
        for (int j = 0; j < output_objects.size() - i - 1; j++)
        {
            if (output_objects[j].time > output_objects[j + 1].time)
            {
                tmp = output_objects[j];
                output_objects[j] = output_objects[j + 1];
                output_objects[j + 1] = tmp;
            }
        }
    }
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    
    thread thread1 (first_line);
    thread thread2 (second_line);
    thread thread3 (third_line);
    
    fill_objects(4);
    
    for (int i = 0; i < input_objects.size(); i++)
    {
        mtx1.lock();
        queue1.push(input_objects[i]);
        mtx1.unlock();
        sleep(3);
    }
    
    cout << "Size: " << input_objects.size() << endl;
    
    if (thread1.joinable())
    {
        thread1.join();
    }
    
    if (thread2.joinable())
    {
        thread2.join();
    }
    
    if (thread3.joinable())
    {
        thread3.join();
    }
    
    cout << "All objects passed the conveyor" << endl;
    
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ms = chrono::duration_cast<std::chrono::seconds>(dur).count();
    
    cout << "Time: " << ms << " sec" << endl;
    
    sort_log();
    ofstream file;
    file.open("log.txt");
    for (int i = 0; i < output_objects.size(); i++)
    {
        file << i << " " << output_objects[i].index << output_objects[i].str;
    }
    file.close();
    return 0;
}
