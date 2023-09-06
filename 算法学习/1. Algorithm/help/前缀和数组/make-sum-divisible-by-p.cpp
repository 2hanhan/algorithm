/**
 * @file make-sum-divisible-by-p.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-04
 * 1590. 使数组和能被 P 整除
 * https://leetcode.cn/problems/make-sum-divisible-by-p/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minSubarray(vector<int> &nums, int p)
    {
        int mod = 0; // 总的余数
        for (int i = 0; i < nums.size(); i++)
        {
            mod = (mod + nums[i]) % p;
        }

        if (mod == 0)
            return 0;

        int min_length = nums.size();
        int cur_mod = 0; // 当前的余数
        unordered_map<int, int> map;
        map[0] = -1;

        for (int i = 0; i < nums.size(); i++)
        {
            cur_mod = (cur_mod + nums[i]) % p;
            int need_mod = (cur_mod - mod + p) % p; // mod = cur_mod - need_mod 两个玩意的余数应该相等，但是不确定谁大谁小统一加个p
            if (map.find(need_mod) != map.end())
            {
                min_length = min(min_length, i - map[need_mod]);
            }

            map[cur_mod] = i;
        }

        return min_length == nums.size() ? -1 : min_length;
    }
};