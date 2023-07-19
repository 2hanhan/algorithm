/**
 * @file combination-sum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 39. 组合总和
 * https://leetcode.cn/problems/combination-sum/
 * 题目条件应该是无重复的正整数数组
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

    void backTracking(vector<int> &candidates, int sum, int startIndex)
    {
        if (sum == 0)
        {
            result.push_back(path);
            return;
        }
        if (sum < 0)
        {
            return;
        }

        for (int i = startIndex; i < candidates.size(); i++)
        {
            path.push_back(candidates[i]);
            sum -= candidates[i];
            backTracking(candidates, sum, i);
            path.pop_back();
            sum += candidates[i];
        }
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        result.clear();
        path.clear();
        backTracking(candidates, target, 0);
        return result;
    }
};