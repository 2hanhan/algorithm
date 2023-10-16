/**
 * @file 29_06.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-16
 * 69. x 的平方根
 * https://leetcode.cn/problems/sqrtx/description/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 高斯牛顿法 测试了一下最少20次迭代能通过所有测试案例
class Solution
{
public:
    int mySqrt(int x)
    {
        double a = 1; // 随便给个初值
        // f = a^2-x
        // J = 2a,H = 4a^2
        // Hdx = -Jf
        // dx = -a/2 +x/(2*a)
        for (int i = 0; i < 20; i++)
        {
            a += -a / 2 + x / (2 * a);
        }
        return a;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    double x = 2.0;
    auto result = solution.mySqrt(x);
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
