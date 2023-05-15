/**
 * @file non-overlapping-intervals.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 * 435. 无重叠区间
 * https://leetcode.cn/problems/non-overlapping-intervals/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        return a[1] < b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        if (intervals.size() == 0)
            return 0;

        sort(intervals.begin(), intervals.end(), cmp);
        int result = 1; // 可以拆分为非重叠区间个数
        int right = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] >= right)//等于的不算是重叠
            {
                result++;
                right = intervals[i][1];
            }
        }
        return intervals.size()-result;
    }
};