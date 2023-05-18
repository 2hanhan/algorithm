/**
 * @file longest-common-subsequence.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 1143. 最长公共子序列
 * https://leetcode.cn/problems/longest-common-subsequence/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        int m = text1.size();
        int n = text2.size();

        vector<vector<int>> dp(m, vector<int>(n, 0));
        int result = 0;
        // 初始化
        int same = 0;
        for (int i = 0; i < m; i++)
        {
            if (text1[i] == text2[0])
            {
                same = 1;
            }
            dp[i][0] = same;
        }
        same = 0;
        for (int j = 0; j < n; j++)
        {
            if (text1[0] == text2[j])
            {
                same = 1;
            }
            dp[0][j] = same;
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (text1[i] == text2[j])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
        return dp[m - 1][n - 1];
    }
};