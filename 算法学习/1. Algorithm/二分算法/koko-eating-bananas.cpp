/**
 * @file koko-eating-bananas.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-09
 * 875. 爱吃香蕉的珂珂
 * https://leetcode.cn/problems/koko-eating-bananas/
 * @copyright Copyright (c) 2023
 *
 */
#include <bits/stdc++.h>
using namespace std;

// 二分法
class Solution
{
public:
    bool can(const vector<int> &piles, const int &h, const int &speed)
    {
        int time = 0;

        for (int i = 0; i < piles.size(); i++)
        {
            time += (piles[i] + speed - 1) / speed; // 此次耗时
            if (time > h)
                return false;
        }
        return true;
    }
    int minEatingSpeed(vector<int> &piles, int h)
    {
        int l = 1;
        int r = 0;

        for (int i = 0; i < piles.size(); i++)
        {
            r = max(r, piles[i]);
        }

        // 在l到r之间二分
        int ans = 0;
        int m = 0;
        while (l <= r)
        {
            m = l + ((r - l) >> 1);
            if (can(piles, h, m))
            {
                ans = m; // 记录能符合条件的结果
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