/**
 * @file longest-palindromic-subsequence.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 516. 最长回文子序列
 * https://leetcode.cn/problems/longest-palindromic-subsequence/
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
    int longestPalindromeSubseq(string s)
    {
        int size = s.size();
        vector<vector<int>> dp(size, vector<int>(size, 0)); // 从i到j的最长回文子序列长度

        for (int i = size - 1; i >= 0; i--)
        {
            for (int j = i; j < size; j++)
            {
                if (i + 1 >= j)
                {
                    if (s[i] == s[j])
                        dp[i][j] = j - i + 1;
                }
                else
                {
                    if (s[i] == s[j])
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    else
                        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][size - 1];
    }
};
