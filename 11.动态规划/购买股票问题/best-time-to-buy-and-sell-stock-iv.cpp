/**
 * @file best-time-to-buy-and-sell-stock-iv.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 188. 买卖股票的最佳时机 IV
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int size = prices.size();
        if (size == 0)
            return 0;
        vector<vector<int>> dp(size, vector<int>(2 * k + 1, 0));
        // j = 0 ， 无操作
        // j = 2*k-1 ，第k次买入
        // j = 2*k ，第k次卖出

        for (int i = 0; i < 2 * k + 1; i++)
        {
            if (i % 2 == 1)
                dp[0][i] = -prices[0];
        }

        for (int i = 1; i < size; i++)
        {
            for (int j = 0; j < 2 * k - 1; j += 2)
            {
                dp[i][j + 1] = max(dp[i - 1][j] - prices[i], dp[i - 1][j + 1]);
                dp[i][j + 2] = max(dp[i - 1][j + 1] + prices[i], dp[i - 1][j + 2]);
            }
        }

        return dp[size - 1][2 * k];
    }
};