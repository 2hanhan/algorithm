/**
 * @file longest-continuous-increasing-subsequence.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 674. 最长连续递增序列
 * https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;

class Solution
{
public:
    int findLengthOfLCIS(vector<int> &nums)
    {
        int size = nums.size();
        if (size <= 1)
            return size;
        int result = 1;
        vector<int> dp(size, 1);
        for (int i = 1; i < size; i++)
        {
            if (nums[i] > nums[i - 1])
                dp[i] = dp[i - 1] + 1;

            if (result < dp[i])
                result = dp[i];
        }
        return result;
    }
};