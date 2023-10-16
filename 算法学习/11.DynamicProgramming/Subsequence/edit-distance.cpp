/**
 * @file edit-distance.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 72. 编辑距离
 * https://leetcode.cn/problems/edit-distance/
 * @copyright Copyright (c) 2023
 *
 */
#include <bits/stdc++.h>
using namespace std;

// 暴力递归 超时
class Solution0
{
public:
    int process(const string &word1, const string &word2, int i, int j)
    {
        // base case
        // 其中一个为0，则把另一个全部删除编辑距离是另一个的长度
        if (i == 0)
        {
            return j;
        }
        if (j == 0)
        {
            return i;
        }

        // 如果第i,j位置字母一样则编辑距离与i-1，j-1相同
        if (word1[i - 1] == word2[j - 1])
        {
            return process(word1, word2, i - 1, j - 1);
        }
        // 如果第i,j位置字母不一样，则编辑距离
        else
        {
            int p1 = process(word1, word2, i - 1, j - 1) + 1; // 替换i-1或j-1位置
            int p2 = process(word1, word2, i, j - 1) + 1;     // 删除i-1位置
            int p3 = process(word1, word2, i - 1, j) + 1;     // 删除j-1位置
            return min<int>(min<int>(p1, p2), p3);
        }
    }
    int minDistance(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();
        return process(word1, word2, m, n);
    }
};

// 动态规划 以结尾位置划分
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // base case
        for (int j = 0; j <= n; j++)
        {
            dp[0][j] = j;
        }
        for (int i = 0; i <= m; i++)
        {
            dp[i][0] = i;
        }

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min<int>(dp[i - 1][j], min<int>(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
                }
            }
        }

        return dp[m][n];
    }
};

class Solution1
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // word1[0，i-1]与word2[0,j-1]相等需要的编辑操作个数
        // 初始化
        for (int i = 0; i < m + 1; i++)
            dp[i][0] = i;
        for (int j = 0; j < n + 1; j++)
            dp[0][j] = j;

        for (int i = 1; i < m + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1]; // 不需要多余操作
                else
                    dp[i][j] = min({dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1, dp[i][j - 1] + 1}); // 从之前的多加一步操作
            }
        }
        return dp[m][n];
    }
};

int main()
{
    string word1 = "";
    string word2 = "a";

    Solution solution;
    cout << solution.minDistance(word1, word2) << endl;
}