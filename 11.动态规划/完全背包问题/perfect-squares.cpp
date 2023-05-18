/**
 * @file perfect-squares.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 279. 完全平方数
 * https://leetcode.cn/problems/perfect-squares/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <limits.h>
using namespace std;
class Solution
{
public:
    int numSquares(int n)
    {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i * i <= n; i++)
        {
            for (int j = i * i; j <= n; j++)
            {
                if (dp[j - i * i] != INT_MAX)
                    dp[j] = min(dp[j], 1 + dp[j - i * i]);
            }
        }
        if (dp[n] == INT_MAX)
            return -1;
        return dp[n];
    }
};