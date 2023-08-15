/**
 * @file subsets.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 78. 子集
 * https://leetcode.cn/problems/subsets/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;
    void backTracking(vector<int> &nums, int stratIndex)
    {
        // 取子集每个都结果都加入
        result.push_back(path);
        if (stratIndex == nums.size())
            return;

        for (int i = stratIndex; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            backTracking(nums, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        result.clear();
        path.clear();
        backTracking(nums, 0);
        return result;
    }
};

