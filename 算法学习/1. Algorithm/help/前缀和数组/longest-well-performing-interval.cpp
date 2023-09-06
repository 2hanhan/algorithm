/**
 * @file longest-well-performing-interval.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-04
 * 1124. 表现良好的最长时间段
 * https://leetcode.cn/problems/longest-well-performing-interval/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longestWPI(vector<int> &hours)
    {

        int max_length = 0;
        int sum = 0;

        unordered_map<int, int> map;
        map[0] = -1;

        for (int i = 0; i < hours.size(); i++)
        {
            int cur = 0;
            if (hours[i] <= 8)
            {
                cur = -1;
            }
            else
            {
                cur = 1;
            }

            sum += cur;

            if (sum - 1 <= 0)
            {
                // 如果不超过一半，则需要求和为【sum -1】时的位置index，这样数组[index+1,i]求和刚好能超过一半
                if (map.find(sum - 1) != map.end())
                {
                    max_length = max(max_length, i - map[sum - 1]);
                }
            }
            else
            {
                max_length = i + 1; // 直接符合大于8小时的超过一半
            }

            if (map.find(sum) == map.end())
            {
                map[sum] = i;
            }
        }

        return max_length;
    }
};