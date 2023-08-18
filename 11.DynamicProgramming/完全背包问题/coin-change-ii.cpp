/**
 * @file coin-change-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 518. 零钱兑换 II
 * https://leetcode.cn/problems/coin-change-ii/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

// 暴力递归 超时
class Solution
{
public:
    int process(const vector<int> &coins, int index, int rest)
    {
        // base case
        if (rest == 0)
            return 1;
        if (rest < 0 || index == coins.size())
            return 0;

        // 取当前index的coins
        int p1 = 0;
        int rest1 = rest;
        while (rest1 >= 0)
        {
            rest1 -= coins[index];
            p1 += process(coins, index + 1, rest1);
        }

        // 不取当前index的coins
        int p2 = process(coins, index + 1, rest);

        return p1 + p2;
    }

    int change(int amount, vector<int> &coins)
    {
        return process(coins, 0, amount);
    }
};

// 记忆化搜索 AC
class Solution
{
public:
    vector<vector<int>> dp;
    int process(const vector<int> &coins, int index, int rest)
    {
        // base case
        if (rest == 0)
            return 1;
        if (rest < 0 || index == coins.size())
            return 0;

        if (dp[index][rest] != -1)
            return dp[index][rest];

        // 取当前index的coins
        int p1 = 0;
        int rest1 = rest;
        while (rest1 >= 0)
        {
            rest1 -= coins[index];
            p1 += process(coins, index + 1, rest1);
        }

        // 不取当前index的coins
        int p2 = process(coins, index + 1, rest);

        dp[index][rest] = p1 + p2;
        return dp[index][rest];
    }

    int change(int amount, vector<int> &coins)
    {
        dp.resize(coins.size() + 1, vector<int>(amount + 1, -1));
        return process(coins, 0, amount);
    }
};

// 动态规划
class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        vector<int> DP(amount + 1, 0);
        DP[0] = 1;

        for (int i = 0; i < coins.size(); i++)
        {
            for (int j = coins[i]; j <= amount; j++)
            {
                DP[j] += DP[j - coins[i]];
            }
        }

        return DP[amount];
    }
};