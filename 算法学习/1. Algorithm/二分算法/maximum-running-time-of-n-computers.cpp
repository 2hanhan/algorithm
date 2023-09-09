/**
 * @file maximum-running-time-of-n-computers.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-09
 * 2141. 同时运行 N 台电脑的最长时间
 * https://leetcode.cn/problems/maximum-running-time-of-n-computers/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 贪心判断能够满足n个电脑运行m分钟
    bool can(const vector<int> &batteries, int n, const long long &m)
    {
        long long sum = 0;

        for (int i = 0; i < batteries.size(); i++)
        {
            if (batteries[i] >= m)
            {
                n--;
            }
            else
            {
                sum += batteries[i];
            }
        }

        return sum >= n * m;
    }

    long long maxRunTime(int n, vector<int> &batteries)
    {

        long long ans;
        long long l = 0;
        long long r = 0;

        int max_batterie = 0;
        for (int i = 0; i < batteries.size(); i++)
        {
            r += batteries[i];
            max_batterie = max(max_batterie, batteries[i]);
        }

        // 剪枝全是碎片电池
        if (r > (long)max_batterie * n)
        {
            return r / n;
        }

        r = max_batterie;//全是碎片电池不能满足，则r的最多范围是max_batterie

        while (l <= r)
        {
            long long m = l + ((r - l) >> 1);
            if (can(batteries, n, m))
            {
                l = m + 1;
                ans = m;
            }
            else
            {
                r = m - 1;
            }
        }

        return ans;
    }
};