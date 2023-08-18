/**
 * @file maximum-length-of-repeated-subarray.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 718. 最长重复子数组
 * https://leetcode.cn/problems/maximum-length-of-repeated-subarray/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;

class Solution
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        if (m == 0 || n == 0)
            return 0;

        vector<vector<int>> dp(m, vector<int>(n, 0));

        // 初始化
        int result = 0;
        for (int i = 0; i < m; i++)
        {
            if (nums1[i] == nums2[0])
            {
                dp[i][0] = 1;
                result = 1;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (nums1[0] == nums2[i])
            {
                dp[0][i] = 1;
                result = 1;
            }
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (nums1[i] == nums2[j])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                if (result < dp[i][j])
                    result = dp[i][j];
            }
        }
        return result;
    }
};