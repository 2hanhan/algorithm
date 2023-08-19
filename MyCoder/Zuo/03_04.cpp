/**
 * @file 03_04.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-18
 * 最多可以同时有多少场比赛
给定一个数组arr，代表每个人的能力值。
再给定一个非负数k如果两个人能力差值正好为k，
那么可以凑在一起比赛一局比赛只有两个人,
返回最多可以同时有多少场比赛
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 贪心
class Solution
{
public:
    int get_max_num(vector<int> &people, int k)
    {
        int size = people.size();
        if (size <= 1)
            return 0;

        sort(people.begin(), people.end(), less<int>()); // 先排序

        int result = 0;
        int left = 0, right = 0;
        bool usedR[size];
        memset(usedR, false, sizeof(usedR));

        while (left < size && right < size) // 不能超过范围
        {
            if (usedR[left]) // 用过了下一个
            {
                left++;
            }
            else if (left >= right)
            {
                right++; // 窗口中只剩余一个
            }
            else
            {
                if (right - left == k) // 能比赛
                {
                    result++;
                    usedR[right++] = true; // 用过了
                    left++;                // 用过了
                }
                else if (right - left < k)
                {
                    right++;
                }
                else
                {
                    left++;
                }
            }
        }
        return result;
    }
};

int main()
{
    Solution solution;

    return 0;
}