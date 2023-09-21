/**
 * @file 23_05.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-13
 * 1000. 合并石头的最低成本
 * https://leetcode.cn/problems/minimum-cost-to-merge-stones/description/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 动态规划 记忆化搜索 范围上的尝试模型
class Solution
{
public:
    int hashfun(int l, int r, int p)
    {
        return l * 100 * 100 + r * 100 + p;
    }
    unordered_map<int, int> can_cost;
    vector<int> sums;

    // [l,r]范围和成p份的代价
    int process(const vector<int> &stones, int k, int l, int r, int p)
    {
        int index = hashfun(l, r, p);
        if (can_cost.find(index) != can_cost.end())
            return can_cost[index];

        if (l == r)
        {
            can_cost[index] = p == 1 ? 0 : -1; // 如果区间只有一个数，只有p份数等于1才行
            return can_cost[index];
        }

        if (p == 1)
        {
            int pre = process(stones, k, l, r, k); // 1份只能由k份合并获得
            if (pre == -1)
            {
                can_cost[index] = -1;
                return can_cost[index];
            }
            else
            {
                can_cost[index] = sums[r + 1] - sums[l] + pre; // 能合成则代价等于 【此次代价】+【先前的合成代价】
                return can_cost[index];
            }
        }
        else
        {
            int ans = INT_MAX;
            for (int i = l; i < r; i++)
            {
                int left = process(stones, k, l, i, 1);
                if (left == -1)
                    continue;
                int right = process(stones, k, i + 1, r, p - 1);
                if (right == -1)
                    continue;
                int all = left + right;
                ans = min(all, ans);
            }
            can_cost[index] = ans == INT_MAX ? -1 : ans;
            return can_cost[index];
        }
    }

    int mergeStones(vector<int> &stones, int k)
    {
        int n = stones.size();
        sums.resize(n + 1, 0);
        // 前缀和数组
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += stones[i];
            sums[i + 1] = sum;
        }

        return process(stones, k, 0, n - 1, 1);
    }
};

// 暴力解法 超市
class Solution1
{
public:
    // [l,r]范围和成p份的代价
    int process(const vector<int> &stones, int k, int l, int r, int p)
    {
        if (l == r)
        {
            return p == 1 ? 0 : -1; // 如果区间只有一个数，只有p份数等于1才行
        }

        if (p == 1)
        {
            int pre = process(stones, k, l, r, k); // 1份只能由k份合并获得
            if (pre == -1)
                return -1;
            else
                return sums[r + 1] - sums[l] + pre; // 能合成则代价等于 【此次代价】+【先前的合成代价】
        }
        else
        {
            int ans = INT_MAX;
            for (int i = l; i < r; i++)
            {
                int left = process(stones, k, l, i, 1);
                if (left == -1)
                    continue;
                int right = process(stones, k, i + 1, r, p - 1);
                if (right == -1)
                    continue;
                int all = left + right;
                ans = min(all, ans);
            }
            return ans == INT_MAX ? -1 : ans;
        }
    }
    vector<int> sums;
    int mergeStones(vector<int> &stones, int k)
    {
        int n = stones.size();
        sums.resize(n + 1, 0);
        // 前缀和数组
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += stones[i];
            sums[i + 1] = sum;
        }

        return process(stones, k, 0, n - 1, 1);
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<int> stones = {3, 2, 4, 1};
    int k = 2;
    auto result = solution.mergeStones(stones, k);
    cout << "result:" << result << endl;

    // 结束计时
    auto end = std::chrono::high_resolution_clock::now();

    // 计算耗时
    std::chrono::duration<double> duration = end - start;
    double seconds = 1000 * duration.count();

    // 输出结果
    std::cout << endl;
    std::cout << "Elapsed time: " << std::fixed << std::setprecision(2) << seconds << " ms\n";

    return 0;
}