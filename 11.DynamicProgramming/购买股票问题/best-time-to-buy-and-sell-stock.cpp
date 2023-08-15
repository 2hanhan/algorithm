/**
 * @file best-time-to-buy-and-sell-stock.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 121. 买卖股票的最佳时机
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
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
        int len = prices.size();
        if (len == 0)
            return 0;
        // dp[i][1] 第i天持有股票
        // dp[i][0] 第i天不持有股票
        vector<vector<int>> dp(len, vector<int>(2));
        dp[0][1] = -prices[0];
        dp[0][0] = 0;
        for (int i = 1; i < len; i++)
        {
            dp[i][1] = max(dp[i - 1][1], -prices[i]);//没买早，之前买早了，做时光机退了，今天买
            dp[i][0] = max(dp[i - 1][1] + prices[i], dp[i - 1][0]);//今天卖，之前卖过了或之前没买
        }
        return dp[len - 1][0];
    }
};