/**
 * @file n-queens.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 * N 皇后问题
 *
 * https://leetcode.cn/problems/n-queens/
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void printall2(vector<vector<string>> &result)
{
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j] << endl;
        }
        cout << endl;
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

class Solution
{
public:
    void putQueens(vector<int> &position, vector<vector<int>> &result, int n)
    {
        if (position.size() == n)
        {
            result.push_back(position);
            return;
        }

        // 尝试每一个列的位置
        for (int i = 0; i < n; i++)
        {
            if (isValid(position, i))
            {
                putQueens(position, result, n);
            }
        }
        //全都尝试过了，不行则
        position.resize(position.size() - 1);
    }

    bool isValid(vector<int> &position, int c)
    {
        // 取出最新加入的一个检验，因为之前的都检验过了
        int r = position.size(); // 行号
        // 按照行遍历一定不同行
        for (int i = 0; i < r; i++)
        {
            // 判断列和对角线
            if (c == position[i] || abs(r - i) == abs(c - position[i]))
            {
                return false;
            }
        }
        // 校验通过加入到其中
        position.push_back(c);
        return true;
    }

    vector<vector<string>> solveNQueens(int n)
    {
        vector<int> position;
        vector<vector<int>> resultV;
        putQueens(position, resultV, n);

        vector<vector<string>> result;
        for (int i = 0; i < resultV.size(); i++)
        {
            vector<string> a_result(n, string(n, '.'));
            for (int j = 0; j < resultV[i].size(); j++)
            {
                a_result[j][resultV[i][j]] = 'Q';
            }
            result.push_back(a_result);
        }
        return result;
    }
};

int main()
{
    vector<int> A, B, C;
    int N;
    cout << "输入塔层数 N:";
    cin >> N;
    Solution solution;
    auto result = solution.solveNQueens(N);
    cout << endl;
    printall2(result);
    cout << endl;
    return 0;
}