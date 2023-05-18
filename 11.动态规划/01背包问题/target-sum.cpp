/**
 * @file target-sum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 494. 目标和
 * https://leetcode.cn/problems/target-sum/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;

class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {

        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
        }

        if ((sum - target) % 2 == 0 && (sum - target) >= 0)
            sum = (sum - target) >> 1;
        else
            return 0;

        vector<int> DP(sum + 1, 0);
        DP[0] = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = sum; j >= nums[i]; j--)
            {
                DP[j] += DP[j - nums[i]];
            }
        }

        return DP[sum];
    }
};