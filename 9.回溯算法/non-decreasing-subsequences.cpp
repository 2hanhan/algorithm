/**
 * @file non-decreasing-subsequences.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 491. 递增子序列
 * https://leetcode.cn/problems/non-decreasing-subsequences/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;

    void backTracking(vector<int> &nums, int startIndex)
    {
        if (path.size() >= 2)
            result.push_back(path);

        set<int> have;
        for (int i = startIndex; i < nums.size(); i++)
        {
            if (have.count(nums[i]) || (!path.empty() && nums[i] < path[path.size() - 1]))
                continue;

            path.push_back(nums[i]);
            have.insert(nums[i]);
            backTracking(nums, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> findSubsequences(vector<int> &nums)
    {
        result.clear();
        path.clear();

        backTracking(nums, 0);
        return result;
    }
};