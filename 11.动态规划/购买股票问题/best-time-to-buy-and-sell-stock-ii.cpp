/**
 * @file best-time-to-buy-and-sell-stock-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 122. 买卖股票的最佳时机 II
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;
// 贪心
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.size() <= 1)
            return 0;

        int result = 0;
        int pre = prices[0];

        for (int i = 1; i < prices.size(); i++)
        {
            result += prices[i] - pre > 0 ? prices[i] - pre : 0;
            pre = prices[i];
        }
        return result;
    }
};

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
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            dp[i][0] = max(dp[i - 1][1] + prices[i], dp[i - 1][0]);
        }
        return dp[len - 1][0];
    }
};