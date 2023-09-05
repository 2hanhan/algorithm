/**
 * @file 13_01.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-21
 * 卡牌游戏的获胜概率|21点游戏
 有1-10数字的牌，可以有无限组 ，抽到每个数字等概率。
 规则是数字之和小于17可以再抽一次，等于或大于17而且小于21就赢了。
 如果抽到牌数字总和大于等于21就输了。最后求这个人赢的概率。

* 谷歌面试题扩展版
面值为1~N的牌组成一组，
每次你从组里等概率的抽出1~N中的一张
下次抽会换一个新的组，有无限组
当累加和<a时，你将一直抽牌
当累加和>=a且<b时，你将获胜
当累加和>=b时，你将失败
返回获胜的概率，给定的参数为N,a,b
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 暴力递归
class Solution
{
public:
    int n, a, b;
    Solution(int _n, int _a, int _b) : n(_n), a(_a), b(_b)
    {
    }

    // 目前累积和为cur的获胜概率
    double process(int cur)
    {
        // base case
        if (cur >= a && cur < b)
        {
            return 1.0;
        }
        if (cur >= b)
        {
            return 0.0;
        }

        // 暴力递归的枚举过程
        // 可以通过推到f(x+1)-f(x-1)推到出f(x)只和某两个位置的关系，
        // 根据这个关系可以，可以改动态规划，但是要注意公式的适用条件
        // 有点类似高中数学已知递推公式，求通解的处理过程
        double result = 0;
        for (int i = 1; i <= n; i++)
        {
            result += process(cur + i);
        }
        return result / n;
    }

    double win()
    {
        if (n < 1 || a >= b || a < 0 || b < 0)
            return 0.0;
        if (b - a >= n)
            return 1.0;
        return process(0);
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    int n = 10;
    int a = 17;
    int b = 21;
    Solution solution(n, a, b);

    cout << "result:" << solution.win() << endl;

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