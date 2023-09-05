/**
 * @file subarray-sum-equals-k.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-04
 * 560. 和为 K 的子数组
 * https://leetcode.cn/problems/subarray-sum-equals-k/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;


class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> map; // 前缀和sum出现的次数
        map[0] = 1;

        int count = 0;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            count += map[sum - k];
            map[sum]++;
        }
        return count;
    }
};