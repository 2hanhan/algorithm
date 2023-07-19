/**
 * @file house-robber-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 213. 打家劫舍 II
 * https://leetcode.cn/problems/house-robber-ii/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>

using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        if (nums.size() == 1)
            return nums[0];
        if (nums.size() == 2)
            return max(nums[0], nums[1]);

        vector<int> dp1(nums.size() - 1, 0);
        dp1[0] = nums[0];
        dp1[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size() - 1; i++)
        {
            dp1[i] = max(nums[i] + dp1[i - 2], dp1[i - 1]);
        }
        vector<int> dp2(nums.size() - 1, 0);
        dp2[0] = nums[1];
        dp2[1] = max(nums[1], nums[2]);
        for (int i = 3; i < nums.size(); i++)
        {
            dp2[i - 1] = max(nums[i] + dp2[i - 3], dp2[i - 2]);
        }
        return max(dp1[nums.size() - 2], dp2[nums.size() - 2]);
    }
};