/**
 * @file permutations.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 47. 全排列 II
 * https://leetcode.cn/problems/permutations-ii/
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
    void backTracking(vector<int> &nums, vector<bool> &used)
    {
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)//判断当前的层的
                continue;

            if (used[i])//判断之前的层的
                continue;
            used[i] = true;
            path.push_back(nums[i]);
            backTracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(), false);
        backTracking(nums, used);
        return result;
    }
};