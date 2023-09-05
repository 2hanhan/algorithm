/**
 * @file PositivesEqualsNegtivesLongestSubarray.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-04
 * 未排序数组中累加和为给定值的最长子数组系列问题补1
 * https://www.nowcoder.com/practice/545544c060804eceaed0bb84fcd992fb
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    // 等价与把正数看做1，负数看做-1，0还是0
    // 然后求sum等于0的最长子数组长度

    unordered_map<int, int> map; // 前缀和等于sum第一次出现位置
    map[0] = -1;

    int sum = 0;
    int length = 0;
    for (int i = 0; i < n; i++)
    {
        int cur = 0;
        if (nums[i] > 0)
        {
            cur = 1;
        }
        else if (nums[i] == 0)
        {
            cur = 0;
        }
        else
        {
            cur = -1;
        }
        sum += cur;

        if (map.find(sum) != map.end())
        {
            length = max(length, i - map[sum]);
        }
        else
        {
            map[sum] = i;
        }
    }

    cout << length << endl;

    return 0;
}