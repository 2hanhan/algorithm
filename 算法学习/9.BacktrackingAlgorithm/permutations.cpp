/**
 * @file permutations.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 46. 全排列
 * https://leetcode.cn/problems/permutations/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <set>
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
            if (used[i])
                continue;
            used[i] = true;
            path.push_back(nums[i]);
            backTracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        backTracking(nums, used);
        return result;
    }
};