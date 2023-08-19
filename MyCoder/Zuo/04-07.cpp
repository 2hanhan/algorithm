/**
 * @file 04-07.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-18
 * 97. 交错字符串
 * https://leetcode.cn/problems/interleaving-string/
 * 给定三个字符串str1、str2和aim，如果aim包含且仅包含来自str1和str2的所有字符， 而且在aim中属于str1的字符之间保持原来在str1中的顺序，
 * 属于str2的字符之间保持 原来在str2中的顺序，那么称aim是str1和str2的交错组成。实现一个函数，判断aim是 否是str1和str2交错组成
 * 【举例】 str1="AB"，str2="12"。那么"AB12"、"A1B2"、"A12B"、"1A2B"和"1AB2"等都是 str1 和 str2 的 交错组成
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 动态规划
class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {

        int m = s1.size();
        int n = s2.size();
        int k = s3.size();
        if (m + n != k)
            return false;

        bool dp[m + 1][n + 1]; // 取s1前面i个和s2前面j个，组成s3的前i+j个
        memset(dp, false, (m + 1) * (n + 1) * sizeof(bool));

        // base case
        // 有一个为串为空
        dp[0][0] = true;
        for (int i = 1; i <= m; i++)
        {
            dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1]; // 注意下标等于个数减一
            cout << " dp[i][0] :" << dp[i][0];
        }

        for (int j = 1; j <= n; j++)
        {
            dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];
            cout << " dp[0][j] :" << dp[0][j];
        }

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {

                bool p1 = (s3[i + j - 1] == s1[i - 1]) && dp[i - 1][j];
                bool p2 = (s3[i + j - 1] == s2[j - 1]) && dp[i][j - 1];
                dp[i][j] = p1 || p2;
            }
        }

        return dp[m][n];
    }
};

int main()
{
    Solution solution;

    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbcbcac";

    cout << "solution:" << solution.isInterleave(s1, s2, s3) << endl;
    return 0;
}