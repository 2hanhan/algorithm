/**
 * @file 22_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-12
 * 42. 接雨水
 * https://leetcode.cn/problems/trapping-rain-water/
 * @copyright Copyright (c) 2023
 *
 */
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        vector<int> capacity(n); // 每个位置的蓄水量

        int l = 0;
        int heigt_l = height[l];
        int r = n - 1;
        int heigt_r = height[r];

        int sum = 0;
        while (l < r)
        {

            if (heigt_l <= heigt_r)//每次结算高度更小的一边的水量
            {
                sum += max(0, heigt_l - height[l++]);
                heigt_l = max(heigt_l, height[l]);
            }
            else
            {
                sum += max(0, heigt_r - height[r--]);
                heigt_r = max(heigt_r, height[r]);
            }
        }
        return sum;
    }
};