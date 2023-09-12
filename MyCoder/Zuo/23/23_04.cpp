/**
 * @file 23_04.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-12
 * 169. 多数元素
 * https://leetcode.cn/problems/majority-element/description/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

//
// 时间复杂度O(N) 额外空间复杂度O(1)
class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int count = 0; // 统计数组不同的消除后还剩几个
        int value = 0; // 统计数值
        for (int i = 0; i < nums.size(); i++)
        {
            if (count == 0)
            {
                value = nums[i];
                count++;
            }
            else
            {
                if (value == nums[i])
                {
                    count++;
                }
                else
                {
                    count--;
                }
            }
        }

        if (count == 0)
            return -1;

        count = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (value == nums[i])
                count++;
        }
        if (count > nums.size() / 2)
            return value;
        else
            return -1;
    }
};