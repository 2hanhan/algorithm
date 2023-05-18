/**
 * @file distinct-subsequences.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 115. 不同的子序列
 * https://leetcode.cn/problems/distinct-subsequences/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int m = s.size();
        int n = t.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // 使用到s中的第i个，能凑出了多少个t中到第j个的数组，i、j从1开始到m+1、n+1

        // 初始化
        for (int i = 1; i < m + 1; i++)
            dp[i][0] = 1;

        for (int i = 1; i < m + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; // 使用s中第i个 + 不使用s中的第i个
                else
                    dp[i][j] = dp[i - 1][j]; // 不使用s中的第i个
            }
        }
        return dp[m][n];
    }
};