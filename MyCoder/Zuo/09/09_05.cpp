/**
 * @file 09_05.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-21
 * y = f(x)
 * f(x) = x + f(x/10) ,x >0
 * f(x) = 0 ,x =0
 * 已知y求x，
 * y 在 [0,x]单调递增, 同时 y>=x ,所以x可能区间是[0,y]
 * 单调性，二分查找 [0,y]
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int fun(int x)
    {
        // base case
        if (x == 0)
        {
            return 0;
        }

        return x + fun(x / 10);
    }

    int get_x(int y)
    {
        int left = 0;
        int right = y;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int result = fun(mid);
            if (result == y)
            {
                return mid;
            }
            else if (result < y)
            {
                left = mid + 1;
            }
            else
            {

                right = mid - 1;
            }
        }
        return -1;
    }
};

int main()
{
    Solution solution;
    int x = 10;
    int y = solution.fun(x);
    cout << "x=" << x << "y =" << y << "解得 x =" << solution.get_x(y) << endl;

    for (int i = 0; i < 1000; i++)
    {
        cout << "y =" << i << "解得 x =" << solution.get_x(i) << endl;
    }

    return 0;
}