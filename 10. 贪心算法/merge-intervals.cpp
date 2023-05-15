/**
 * @file merge-intervals.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 * 56. 合并区间
 * https://leetcode.cn/problems/merge-intervals/
 * @copyright Copyright (c) 2023
 *
 */
#include <limits.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] < b[0];
    }

    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> result;
        if (intervals.size() == 0)
            return result;
        // 按照左端点排序
        sort(intervals.begin(), intervals.end(), cmp);

        int left = intervals[0][0];
        int right = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++)
        {
            if (right >= intervals[i][0])
            {
                right = right > intervals[i][1] ? right : intervals[i][1]; // right取最大的
            }
            else
            {
                vector<int> one{left, right};
                result.push_back(one);
                // 更新结果
                left = intervals[i][0];
                right = intervals[i][1];
            }
        }
        // 保存最后一组
        vector<int> one{left, right};
        result.push_back(one);

        return result;
    }
};