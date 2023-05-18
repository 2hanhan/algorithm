/**
 * @file best-time-to-buy-and-sell-stock-iii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 123. 买卖股票的最佳时机 III
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/
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
        if (prices.size() <= 1)
            return 0;
        int size = prices.size();
        vector<vector<int>> dp(size, vector<int>(5, 0));

        dp[0][0] = 0; // 从来没买卖过
        dp[0][1] = -prices[0]; // 第一次买后
        dp[0][2] = 0; // 第一次卖后
        dp[0][3] = -prices[0]; // 第二次买后
        dp[0][4] = 0; // 第二次卖后

        for (int i = 1; i < size; i++)
        {
            int dp0 = 0;
            int dp1 = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            int dp2 = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
            int dp3 = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
            int dp4 = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);

            dp[i] = {dp0,dp1,dp2,dp3,dp4};
        }
        return dp[size-1][4];
    }
};