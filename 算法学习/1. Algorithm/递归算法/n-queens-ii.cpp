/**
 * @file n-queens-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 * N 皇后问题 返回解的个数
 * https://leetcode.cn/problems/n-queens-ii/
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution0
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
                position.resize(position.size() - 1); // 把正确的pop出来进行下一次
            }
        }
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
        vector<int> position; // 行号i 列号position[i]
        vector<vector<int>> resultV;
        putQueens(position, resultV, n);

        // 生成对应的string
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

class Solution
{
public:
    int getNQueens(const int &limit, int colLim, int leftDiaLim, int rightDiaLim)
    {
        // 如果colLim占满了
        if (limit == colLim)
            return 1;

        // 可以放置Queen的位
        int pos = limit & (~(colLim | leftDiaLim | rightDiaLim));

        int result = 0;
        while (pos != 0)
        {
            int mostRightOne = pos & (~pos + 1);// 可以放置的pos的最右侧一位
            pos = pos - mostRightOne;
            result += getNQueens(limit,
                                 colLim | mostRightOne,//当前放置过的列
                                 (mostRightOne | leftDiaLim) << 1,//之前存在过的列的左对角线|当前放置过的列的左对角线
                                 (mostRightOne | rightDiaLim) >> 1);//之前存在过的列的右对角线|当前放置过的列的右对角线
        }
        return result;
    }

    int totalNQueens(int n)
    {

        int limit = n == 32 ? -1 : ((1 << n) - 1); // 1的位代表需要放置
        return getNQueens(limit, 0, 0, 0);
    }
};

int main()
{
    vector<int> A, B, C;
    int N;
    cout << "输入皇后个数 N:";
    cin >> N;
    Solution0 solution0;
    auto result0 = solution0.solveNQueens(N);
    int num0 = result0.size();
    cout << "Num0:" << num0 << endl;

    Solution solution;
    int result = solution.totalNQueens(N);
    cout << "result:" << result << endl;
    cout << endl;
    return 0;
}