/**
 * @file hanota-lcci.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
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

// 递归算法
class Solution
{
public:
    void move(vector<int> &from, vector<int> &to)
    {

        int last = from.size() - 1;
        if (last < 0)
            return;
        to.push_back(from[last]);
        from.resize(last);
    }

    void fromtoother(vector<int> &from, vector<int> &to, vector<int> &other, int N)
    {
        if (N <= 1)
        {
            move(from, to);
            return;
        }

        fromtoother(from, other, to, N - 1); // 把N-1放到other上，
        move(from, to);                      // 把N放到to上
        fromtoother(other, to, from, N - 1); // 子任务，把N-1放到to上
    }

    void hanota(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        fromtoother(A, C, B, A.size());
    }
};

int main()
{
    vector<int> A, B, C;
    int N;
    cout << "输入塔层数 N:";
    cin >> N;
    for (int i = N - 1; i >= 0; i--)
    {
        A.push_back(i);
    }
    printall(A);
    printall(B);
    printall(C);
    cout << endl;
    Solution solution;
    solution.hanota(A, B, C);
    printall(A);
    printall(B);
    printall(C);
    cout << endl;
    return 0;
}