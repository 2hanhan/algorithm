/**
 * @file monotone-increasing-digits.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 * 738. 单调递增的数字
 * https://leetcode.cn/problems/monotone-increasing-digits/
 * @copyright Copyright (c) 2023
 *
 */
#include <cmath>
class Solution
{
public:
    int monotoneIncreasingDigits(int n)
    {

        int x10 = 0; // 记录当前到第几位了

        // 个位数
        int left = n;
        int right = left % 10; // 当前最低位

        int cur = right;
        int pre = right;

        while (left / 10 != 0)
        {
            x10++;
            left = left / 10;  // 取剩余的高位数字
            right = left % 10; // 当前最低位
            if (right <= pre)
            {
                cur = right * pow(10, x10) + cur;
                pre = right;
            }
            else
            {
                // 当前位-1，其余的取9
                cur = right * pow(10, x10) - 1;
                pre = right - 1;
            }
        }
        return cur;
    }
};

class Solution
{
public:
    int monotoneIncreasingDigits(int n)
    {

        int x10 = 1; // 记录当前到第几位了

        // 个位数
        int left = n;
        int right = left % 10; // 当前最低位

        int cur = right;
        int pre = right;

        while (left / 10 != 0)
        {
            x10 *= 10;
            left = left / 10;  // 取剩余的高位数字
            right = left % 10; // 当前最低位
            if (right <= pre)
            {
                cur = right * x10 + cur;
                pre = right;
            }
            else
            {
                // 当前位-1，其余的取9
                cur = right * x10 - 1;
                pre = right - 1;
            }
        }
        return cur;
    }
};