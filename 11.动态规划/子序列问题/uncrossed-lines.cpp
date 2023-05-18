/**
 * @file uncrossed-lines.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 1035. 不相交的线
 * https://leetcode.cn/problems/uncrossed-lines/
 * 本质上是求最长公共子序列长度
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

class Solution
{
public:
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i < m + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                if (nums1[i-1] == nums2[j-1])//主要nums1、nums2是从0到m、n
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j-1]);
            }
        }
        return dp[m][n];
    }
};