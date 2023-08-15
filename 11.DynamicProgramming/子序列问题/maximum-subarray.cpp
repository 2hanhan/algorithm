/**
 * @file maximum-subarray.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 53. 最大子数组和
 * https://leetcode.cn/problems/maximum-subarray/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

// DP
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int result = dp[0];
        for (int i = 1; i < nums.size(); i++)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            if (result < dp[i])
                result = dp[i];
        }

        return result;
    }
};