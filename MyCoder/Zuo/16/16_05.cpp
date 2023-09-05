/**
 * @file 16_05.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-30
 * 剑指 Offer 62. 圆圈中最后剩下的数字
 * https://leetcode.cn/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // n 为当前数组长度，m个一组删掉最后一个
    int getindex(int n, int m)
    {
        if (n == 1)
        {
            return 1;
        }
        int pre = getindex(n - 1, m);
        cout << n - 1 << ":" << pre << endl;
        return (pre + m - 1) % n + 1; // 递推关系
    }
    // m = 3，每次删除一个index的变化，并从删除位置重新计数index的变化
    //  1 2 3 4 5 6 【n=6,存在的数index】
    //  4 5 x 1 2 3 【n=5,存在的数index】
    //  1 2 x 3 4 x 【n=4,存在的数index】
    //  2 3 x x 1 x 【n=3,存在的数index】
    //  2 x x x 1(3) x 【n=2,存在的数index】
    //  1 x x x x x 【n=1,存在的数index】
    int lastRemaining(int n, int m)
    {
        return getindex(n, m) - 1;
    }
};

class NodeList
{
public:
    NodeList(int _value) : value(_value)
    {
    }
    int value;
    NodeList *next;
};

// 暴力 超时
class Solution0
{
public:
    int lastRemaining(int n, int m)
    {
        NodeList *head = new NodeList(0);
        NodeList *pre = head;
        for (int i = 1; i < n; i++)
        {

            NodeList *node = new NodeList(i);
            pre->next = node;
            pre = node;
        }
        pre->next = head;

        int num = 1;
        while (pre->next != pre)
        {
            if (num % m == 0)
            {
                pre->next = pre->next->next;
            }
            else
            {
                pre = pre->next;
            }
            num++;
        }
        return pre->value;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    int n = 5;
    int m = 3;
    int result = solution.lastRemaining(n, m);
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