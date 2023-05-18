/**
 * @file best-time-to-buy-and-sell-stock-with-cooldown.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 309. 最佳买卖股票时机含冷冻期
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int size = prices.size();
        if (size == 0)
            return 0;
        vector<vector<int>> dp(size, vector<int>(4, 0));

        dp[0][0] = -prices[0]; // 当天买入或者买入过了
        dp[0][1] = 0;          // 卖过了，能买入新的
        dp[0][2] = 0;          // 当天卖了
        dp[0][3] = 0;          // 冷冻期

        for (int i = 1; i < size; i++)
        {
            dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i]));
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
            dp[i][2] = dp[i - 1][0] + prices[i];
            dp[i][3] = dp[i - 1][2];
        }

        return max(dp[size - 1][3], max(dp[size - 1][2], dp[size - 1][1]));
    }
};