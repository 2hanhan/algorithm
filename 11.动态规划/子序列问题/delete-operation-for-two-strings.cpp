/**
 * @file delete-operation-for-two-strings.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 583. 两个字符串的删除操作
 * https://leetcode.cn/problems/delete-operation-for-two-strings/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <string>
using namespace std;

//DP
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // 初始化
        for (int i = 0; i < m + 1; i++)
            dp[i][0] = i; // 删除i个变成0个

        for (int j = 0; j < n + 1; j++)
            dp[0][j] = j; // 删除j个变成0个
        for (int i = 1; i < m + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
            }
        }
        return dp[m][n];
    }
};

// 方法二：先求最长公共子序列、然后word1+word2总长度 - 2*最长公共子序列长度