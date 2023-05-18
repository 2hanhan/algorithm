/**
 * @file unique-binary-search-trees.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 96. 不同的二叉搜索树
 * https://leetcode.cn/problems/unique-binary-search-trees/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    vector<int> dp;
    int numTrees(int n)
    {
        dp.resize(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i < n + 1; i++)
        {
            // 头结点占一个
            // 剩余的i-1个分配
            for (int j = 0; j < (i - 1) >> 1; j++)
                dp[i] += 2 * dp[j] * dp[i - 1 - j];

            if ((i - 1) % 2 == 0)
                dp[i] += dp[(i - 1) >> 1] * dp[(i - 1) >> 1]; // 偶数个，左右两侧分配个数相等属于一种情况
            else
                dp[i] += 2 * dp[(i - 1) >> 1] * dp[((i - 1) >> 1) + 1]; // 奇数个，左右两侧分配个数不相等
        }
        return dp[n];
    }
};

int main(int argc, char **argv)
{
    cout << endl
         << "输入 n" << endl;
    Solution solution;
    int n;
    cin >> n;
    cout << endl;
    solution.numTrees(n);
    // solution.printDP();
    cout << endl;
    return 0;
}