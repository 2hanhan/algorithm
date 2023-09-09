/**
 * @file split-array-largest-sum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-09
 * 410. 分割数组的最大值
 * https://leetcode.cn/problems/split-array-largest-sum/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 二分法
class Solution
{
public:
    bool can(const vector<int> &nums, const int &k, const int &m)
    {
        int count = 1;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > m)
                return false;

            sum += nums[i];
            if (sum > m)
            {
                count++;
                sum = nums[i];
            }
            if (count > k)
                return false;
        }

        return true;
    }

    int splitArray(vector<int> &nums, int k)
    {
        int ans = 0;
        int l = 0;
        int r = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            r += nums[i];
        }

        while (l <= r)
        {
            int m = l + ((r - l) >> 1);
            if (can(nums, k, m))
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }
};
