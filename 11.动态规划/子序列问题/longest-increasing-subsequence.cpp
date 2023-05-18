/**
 * @file longest-increasing-subsequence.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 300. 最长递增子序列
 * https://leetcode.cn/problems/longest-increasing-subsequence/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;


class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int size = nums.size();
        if (size <= 0)
            return size;
        int result = 0;
        vector<int> dp(size, 1);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                    dp[i] = max(dp[j] + 1, dp[i]);//以nums[i]结尾的最大的长度
            }
            if (dp[i] > result)
                result = dp[i];
        }
        return result;
    }
};