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