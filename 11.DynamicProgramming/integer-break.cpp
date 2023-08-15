/**
 * @file integer-break.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-15
 * 343. 整数拆分
 * https://leetcode.cn/problems/integer-break/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        if (n <= 3) return 1 * (n - 1);
        // 初始化
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;
        for (int i = 4; i <= n ; i++) {
            //尝试不同的拆分，保留最大的情况
            for (int j = 1; j <= i / 2; j++) {
                dp[i] = max(dp[i], dp[i - j] * dp[j]);
            }
        }
        return dp[n];
    }
};
