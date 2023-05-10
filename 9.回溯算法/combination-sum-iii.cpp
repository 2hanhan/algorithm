/**
 * @file combination-sum-iii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 216. 组合总和 III
 * https://leetcode.cn/problems/combination-sum-iii/
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
    void backTracking(int k, int sum, int startIndex)
    {
        if (path.size() == k)
        {
            if (sum == 0)
                result.push_back(path);
            return;
        }
        // 求和以及不足 sum < i + 1
        if (sum < startIndex)
            return;

        // 个数不足 k - path.size() <= 9 - i +1
        for (int i = startIndex; k - path.size() <= 9 - i + 1; i++)
        {
            sum -= i;
            path.push_back(i);
            backTracking(k, sum, i + 1);
            sum += i;
            path.pop_back();
        }

        // 不剪支
        // for (int i = startIndex; i <= 9; i++)
        // {
        //     sum -= i;
        //     path.push_back(i);
        //     backTracking(k, sum, i + 1);
        //     sum += i;
        //     path.pop_back();
        // }
    }
    vector<vector<int>> combinationSum3(int k, int n)
    {
        result.clear();
        path.clear();
        backTracking(k, n, 1);
        return result;
    }
};