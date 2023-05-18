/**
 * @file best-time-to-buy-and-sell-stock-with-transaction-fee.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 714. 买卖股票的最佳时机含手续费
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {

        int size = prices.size();
        if (size == 0)
            return 0;

        vector<vector<int>> dp(size, vector<int>(2, 0));

        dp[0][1] = -prices[0];

        for (int i = 1; i < size; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[size - 1][0];
    }
};