/**
 * @file 17_04.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-30
 * 115. 不同的子序列
 * https://leetcode.cn/problems/distinct-subsequences/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int m = s.size();
        int n = t.size();
        vector<vector<unsigned long long>> dp(m, vector<unsigned long long>(n, 0));

        // base case
        dp[0][0] = s[0] == t[0] ? 1 : 0;

        for (int i = 1; i < m; i++)
        {
            dp[i][0] = s[i] == t[0] ? dp[i - 1][0] + 1 : dp[i - 1][0];
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < min<int>(i + 1, n); j++) // j<=i,s要能凑够t的j个字符
            {
                dp[i][j] = dp[i - 1][j]; // 不使用s[i]
                if (s[i] == t[j])
                {
                    dp[i][j] += dp[i - 1][j - 1]; // 使用s[i]
                }
            }
        }

        return dp[m - 1][n - 1] > INT_MAX ? -1 : dp[m - 1][n - 1]; //! 官方测试用例脑子有坑，非得有一个比大于32位int的结果，完后还不告诉你超出了返回-1
    }
};

int main()
{
    // 开始计时
    auto start = chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    string s = "rabbbit";
    string t = "rabbit";
    int result = solution.numDistinct(s, t);
    cout << "result:" << result << endl;
    // 结束计时
    auto end = chrono::high_resolution_clock::now();

    // 计算耗时
    chrono::duration<double> duration = end - start;
    double seconds = 1000 * duration.count();

    // 输出结果
    cout << endl;
    cout << "Elapsed time: " << fixed << setprecision(2) << seconds << " ms\n";

    return 0;
}
