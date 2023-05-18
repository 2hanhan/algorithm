/**
 * @file coin-change.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 322. 零钱兑换
 * https://leetcode.cn/problems/coin-change/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <limits.h>
using namespace std;
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> dp(amount + 1, -1);

        for (int i = 0; i < coins.size(); i++)
        {
            for (int j = coins[i]; j <= amount; j++)
            {
                if (j == coins[i])
                {
                    dp[j] = 1;
                }
                else if (dp[j] != -1 && dp[j - coins[i]] != -1)
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);
                else if (dp[j] == -1 && dp[j - coins[i]] != -1)
                {
                    dp[j] = dp[j - coins[i]] + 1;
                }
                else if (dp[j] != -1 && dp[j - coins[i]] == -1)
                {
                    dp[j] = dp[j];
                }
                else
                {
                    dp[j] = -1;
                }
            }
        }

        return dp[amount];
    }
};

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++)
        {
            for (int j = coins[i]; j <= amount; j++)
            {
                if (dp[j - coins[i]] != INT_MAX)
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);
            }
        }
        if (dp[amount] == INT_MAX)
            return -1;
        return dp[amount];
    }
};