/**
 * @file combination-sum-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 40. 组合总和 II
 * https://leetcode.cn/problems/combination-sum-ii/
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
            if (i > startIndex && candidates[i] == candidates[i - 1])//去重操作，重复的数字只在第一次使用时进行相同数字的叠加
                continue;

            path.push_back(candidates[i]);
            sum -= candidates[i];
            backTracking(candidates, sum, i + 1);
            path.pop_back();
            sum += candidates[i];
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        result.clear();
        path.clear();
        sort(candidates.begin(), candidates.end());
        backTracking(candidates, target, 0);
        return result;
    }
};