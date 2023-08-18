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
#include <bits/stdc++.h>
#include <memory>

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
    priority_queue<int> priQue;                        // 从小到大方法，大根堆
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

void test_list()
{
    cout << "test_list";

    list<int> myList(5, -1);
    printall(myList);

    list<int>::iterator iter = myList.begin();
    int num = 15;
    while (num > 0)
    {
        iter++;
        if (iter == myList.end())
            cout << endl
                 << num
                 << "iter == myList.end()";
        num--;
    }
    // 迭代器++超过end()后会从begin()重新开始

    myList.insert(iter, 10);
    printall(myList);
}

void test_memset_nums()
{
    int m = 6, n = 5;
    int distance[m][n];
    memset(distance, -1, m * n * sizeof(int));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "[" << i << "," << j << ":" << distance[i][j] << "]";
        }
    }
}

int main(int argc, char **argv)
{
    test_memset_nums();
    cout << endl;
    return 0;
}