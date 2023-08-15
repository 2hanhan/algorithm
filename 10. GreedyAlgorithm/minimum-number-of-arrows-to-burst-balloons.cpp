/**
 * @file minimum-number-of-arrows-to-burst-balloons.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 *
 * @copyright Copyright (c) 2023
 * 452. 用最少数量的箭引爆气球
 */

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
    int findMinArrowShots(vector<vector<int>> &points)
    {
        if (points.size() == 0)
            return 0;
        // 排序
        sort(points.begin(), points.end(), cmp);

        int result = 0;
        int right = points[0][1]; // 不是从0开始贴气球
        for (int i = 1; i < points.size(); i++)
        {
            if (points[i][0] > right)
            {
                result++;             // 处理把之前的气球
                right = points[i][1]; // 更新边界
            }
            else
            {
                right = right < points[i][1] ? right : points[i][1];
            }
        }
        return result + 1; // 处理最后一波气球
    }
};

class Solution
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        return a[1] < b[1];
    }
    int findMinArrowShots(vector<vector<int>> &points)
    {
        if (points.size() == 0)
            return 0;
        // 排序
        sort(points.begin(), points.end(), cmp);

        int result = 0;
        int right = points[0][1]; // 不是从0开始贴气球
        for (int i = 1; i < points.size(); i++)
        {
            if (points[i][0] > right)
            {
                result++;             // 处理把之前的气球
                right = points[i][1]; // 更新边界
            }
        }
        return result + 1; // 处理最后一波气球
    }
};