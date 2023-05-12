/**
 * @file subsets-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 90. 子集 II
 * https://leetcode.cn/problems/subsets-ii/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;
    void backTracking(vector<int> &nums, int startIndex)
    {
        result.push_back(path);
        if (startIndex == nums.size())
        {
            return;
        }

        for (int i = startIndex; i < nums.size(); i++)
        {
            if (i > startIndex && nums[i] == nums[i - 1])
                continue;
            path.push_back(nums[i]);
            backTracking(nums, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        result.clear();
        path.clear();
        sort(nums.begin(),nums.end());
        backTracking(nums, 0);
        return result;
    }
};