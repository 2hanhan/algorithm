/**
 * @file test_unordered_map.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <typeinfo>

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <functional>
using namespace std;

template <class T>
void printall(T &mySTL)
{
    cout << endl
         << typeid(mySTL).name() << ":";
    for (auto iter = mySTL.begin(); iter != mySTL.end(); iter++)
    {
        cout << *iter << " ";
    }
}

void test_unordered_map()
{
    unordered_map<char, int> myunordered_map;

    string mystring = "aaaaddddcccc";
    for (auto iter = mystring.begin(); iter != mystring.end(); iter++)
    {
        cout << "[" << *iter << "]";
        myunordered_map[*iter]++;
    }
}

void test_priority_queue()
{
    priority_queue<int> priQue;           // 从小到大方法，大根堆
    priority_queue<int, vector<int>, less<int>> myQue; // 从小到大方法，大根堆

    vector<int> myVector{9, 1, 2, 5, 7, 4, 3, 6, 8};
    for (auto iter = myVector.begin(); iter != myVector.end(); iter++)
    {
        priQue.push(*iter);
        myQue.push(*iter);
    }

    sort(myVector.begin(), myVector.end(), less<int>());
    cout << endl
         << "less:";
    printall(myVector);

    cout << endl
         << "默认:";
    while (!priQue.empty())
    {
        cout << priQue.top() << " ";
        priQue.pop();
    }
    cout << endl
         << "less:";
    while (!myQue.empty())
    {
        cout << myQue.top() << " ";
        myQue.pop();
    }
}

int main(int argc, char **argv)
{
    test_priority_queue();
    cout << endl;
    return 0;
}