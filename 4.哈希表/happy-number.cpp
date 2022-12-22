/**
 * @file happy-number.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-22
 *
 * @copyright Copyright (c) 2022
 * - 4.4 快乐数
 */

#include <unordered_set>
using namespace std;

class Solution
{
public:
    int getSum(int sum)
    {
        int newsum = 0;
        while (sum)
        {
            newsum += (sum % 10) * (sum % 10); // 累计个、十、百、千...的平方
            sum /= 10;                         // 抹除最低位
        }
        return newsum;
    }
    bool isHappy(int n)
    {
        unordered_set<int> sum_set; // 统计出现的sum

        while (true)
        {
            n = getSum(n); // 计算各位平方和
            if (n == 1)
                return true;

            if (sum_set.find(n) != sum_set.end())
            {
                return false; // sum出现循环则不是快乐数
            }
            else
            {
                sum_set.insert(n); // 保存出现过的sum
            }
        }
    }
};