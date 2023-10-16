/**
 * @file 29_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-16
 * 50. Pow(x, n)
 * https://leetcode.cn/problems/powx-n/description/
 * 官方题解沙雕一样，n给定int，他使用long long取巧
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 贪心 时间复杂度 logN
class Solution
{
public:
    double myPow(double x, int n)
    {
        bool positive = true;
        bool min_negative = false;
        if (n == INT_MIN)
        {
            n = INT_MAX;
            min_negative = true;
            positive = false;
        }
        else if (n < 0)
        {
            n = -n;
            positive = false;
        }

        double result = 1;
        double cur = x;

        while (n != 0)
        {
            if ((n & 1) != 0) // 取出2进制最低1位，如果不为0，则需要*x^(二进制的第几位)
            {
                result *= cur;
            }
            cur *= cur;
            n >>= 1;
        }
        result = min_negative ? result * x : result;
        return positive ? result : 1.0 / result;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    double x = 2.0;
    int n = 10;
    auto result = solution.myPow(x, n);
    cout << "result:" << result << endl;

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
