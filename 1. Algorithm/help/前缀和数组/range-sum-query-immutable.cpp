/**
 * @file range-sum-query-immutable.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-04
 * 303. 区域和检索 - 数组不可变
 * https://leetcode.cn/problems/range-sum-query-immutable/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class NumArray
{
public:
    vector<int> help;
    NumArray(vector<int> &nums)
    {
        help.resize(nums.size() + 1, 0); // 多一个可以减少边界讨论的情况

        for (int i = 0; i < nums.size(); i++)
        {
            help[i + 1] = help[i] + nums[i];
        }
    }

    int sumRange(int left, int right)
    {
        return help[right + 1] - help[left];
    }
};
