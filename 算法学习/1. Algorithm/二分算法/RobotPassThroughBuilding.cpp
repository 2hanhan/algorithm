/**
 * @file RobotPassThroughBuilding.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-09
 * 机器人跳跃问题
 * https://www.nowcoder.com/practice/7037a3d57bbd4336856b8e16a9cafd71
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool can(const vector<int> &nums, const int &max, const int &m)
{
    int cur = m;
    for (int i = 0; i < nums.size(); i++)
    {
        cur = cur + (cur - nums[i]);
        if (cur >= max)
            return true;

        if (cur < 0)
            return false;
    }
    return true;
}

// 二分法
int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    int max_num = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
        max_num = max(max_num, nums[i]);
    }

    int ans = 0;
    int l = 0;
    int r = max_num;

    while (l <= r)
    {
        int m = l + ((r - l) >> 2);
        if (can(nums, max_num, m))
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }

    cout << ans << endl;
    return 0;
}