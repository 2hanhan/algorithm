/**
 * @file maximum-subarray.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 53. 最大子数组和
 * https://leetcode.cn/problems/maximum-subarray/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

// 贪心
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int result = nums[0];
        int sum = result;
        for (int i = 1; i < nums.size(); i++)
        {
            if (sum < 0)//如果先前的求和sum为负数，那么加元素nums[i]一定会不如只取nums[i]值大
                sum = 0;//所以sum归零，从nums[i]开始重新求和

            sum += nums[i];
            if (sum > result)
                result = sum;
        }
        return result;
    }
};