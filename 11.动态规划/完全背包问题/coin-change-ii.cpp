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