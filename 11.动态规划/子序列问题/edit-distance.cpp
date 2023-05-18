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
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));//word1[0，i-1]与word2[0,j-1]相等需要的编辑操作个数
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