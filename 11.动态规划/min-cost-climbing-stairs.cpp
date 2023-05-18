/**
 * @file min-cost-climbing-stairs.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-15
 * 746. 使用最小花费爬楼梯
 * https://leetcode.cn/problems/min-cost-climbing-stairs/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;
class Solution
{
public:
    vector<int> mincost;
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        mincost.resize(n + 1, 0);

        for (int i = 2; i < n + 1; i++)
        {
            int c1 = mincost[i - 2] + cost[i - 2];
            int c2 = mincost[i - 1] + cost[i - 1];

            mincost[i] = c1 < c2 ? c1 : c2;
        }
        return mincost[n];
    }
};