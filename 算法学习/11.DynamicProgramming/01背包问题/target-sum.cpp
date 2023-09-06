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
        target = target > 0? target : -target;

        // 奇、偶性一致，目标targrt要小于等于sum
        if ((sum - target) % 2 == 0 && sum >= target)
            sum = (sum + target) >> 1;//P-N=T  => P = (S+T)/2
        else
            return 0;

        vector<int> DP(sum + 1, 0);
        DP[0] = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = sum; j >= nums[i]; j--)
            {
                DP[j] += DP[j - nums[i]];//用j位置的数+不用j位置的数凑出来sum
            }
        }

        return DP[sum];
    }
};