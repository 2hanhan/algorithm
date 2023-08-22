/**
 * @file 08_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 双指针
class Solution
{
public:
    int maxArea(vector<int> &height)
    {

        int result = 0;
        int L = 0, R = height.size() - 1;
        while (L < R)
        {
            // 从两边往中间收缩
            // 每次移动比较矮的那个，有可能使得存储量比上一次有所增加
            if (height[L] > height[R])
            {
                int cur = (R - L) * height[R];
                result = result > cur ? result : cur;
                R--;
            }
            else
            {
                int cur = (R - L) * height[L];
                result = result > cur ? result : cur;
                L++;
            }
        }
        return result;
    }
};

int main()
{
    Solution solution;
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    cout << solution.maxArea(height) << endl;

    return 0;
}