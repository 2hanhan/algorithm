/**
 * @file 10_05.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-21
 * 面试题 08.14. 布尔运算
 * https://leetcode.cn/problems/boolean-evaluation-lcci/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 动态规划
class Solution
{
public:
    vector<vector<pair<int, int>>> dp;
    pair<int, int> process(string s, int L, int R)
    {
        if (dp[L][R].first != -1)
            return dp[L][R];

        // base case
        if (L == R)
        {
            dp[L][R].first = s[L] == '1' ? 1 : 0;  // 为true的方法数
            dp[L][R].second = s[L] == '0' ? 1 : 0; // 为false的方法数
            // cout << dp[L][R].first << " " << dp[L][R].second << endl;
            return dp[L][R];
        }
        else
        {
            dp[L][R].first = 0;
            dp[L][R].second = 0;
            for (int split = L + 1; split < R; split += 2)
            {
                auto left = process(s, L, split - 1);
                auto right = process(s, split + 1, R);
                int ts = 0, fs = 0;
                if (s[split] == '|')
                {
                    ts = left.first * right.first + left.first * right.second + left.second * right.first; // 1|1 1|0 0|1
                    fs = left.second * right.second;                                                       // 0|0
                }
                else if (s[split] == '&')
                {
                    ts = left.first * right.first;                                                           // 1&1
                    fs = left.first * right.second + left.second * right.first + left.second * right.second; // 1&0 0&1 0&0
                }
                else if (s[split] == '^')
                {
                    ts = left.first * right.second + left.second * right.first; // 1^0 0^1
                    fs = left.first * right.first + left.second * right.second; // 1^1 0^0
                }
                dp[L][R].first += ts;
                dp[L][R].second += fs;
            }
            return dp[L][R];
        }
    }

    int countEval(string s, int result)
    {
        dp.resize(s.size(), vector<pair<int, int>>(s.size(), pair<int, int>(-1, -1)));
        if (result == 1)
            return process(s, 0, s.size() - 1).first;
        else
            return process(s, 0, s.size() - 1).second;
    }
};

// 暴力递归 超时
class Solution1
{
public:
    pair<int, int> process(string s, int L, int R)
    {
        int t = 0;
        int f = 0;
        // base case
        if (L == R)
        {
            t = s[L] == '1' ? 1 : 0; // 为true的方法数
            f = s[L] == '0' ? 1 : 0; // 为false的方法数
            return {t, f};
        }
        else
        {

            for (int split = L + 1; split < R; split += 2)
            {
                auto left = process(s, L, split - 1);
                auto right = process(s, split + 1, R);
                int ts = 0, fs = 0;
                if (s[split] == '|')
                {
                    ts = left.first * right.first + left.first * right.second + left.second * right.first; // 1|1 1|0 0|1
                    fs = left.second * right.second;                                                       // 0|0
                }
                else if (s[split] == '&')
                {
                    ts = left.first * right.first;                                                           // 1&1
                    fs = left.first * right.second + left.second * right.first + left.second * right.second; // 1&0 0&1 0&0
                }
                else if (s[split] == '^')
                {
                    ts = left.first * right.second + left.second * right.first; // 1^0 0^1
                    fs = left.first * right.first + left.second * right.second; // 1^1 0^0
                }
                t += ts;
                f += fs;
            }
            return {t, f};
        }
    }

    int countEval(string s, int result)
    {
        if (result == 1)
            return process(s, 0, s.size() - 1).first;
        else
            return process(s, 0, s.size() - 1).second;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    string s = "0";
    int result = 0;
    cout << "result:" << solution.countEval(s, result) << endl;

    // 结束计时
    auto end = std::chrono::high_resolution_clock::now();

    // 计算耗时
    std::chrono::duration<double> duration = end - start;
    double seconds = 1000 * duration.count();

    // 输出结果
    std::cout << endl;
    std::cout << "Elapsed time: " << std::fixed << std::setprecision(2) << seconds << " ms\n";

    return 0;
}