/**
 * @file is-subsequence.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 392. 判断子序列
 * https://leetcode.cn/problems/is-subsequence/
 * @copyright Copyright (c) 2023
 *
 */

#include <string>
#include <vector>
using namespace std;

// DP
class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        int m = s.size();
        int n = t.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i < m + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n] == s.size();
    }
};