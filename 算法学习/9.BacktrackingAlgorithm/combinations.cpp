/**
 * @file combinations.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 77. 组合
 * https://leetcode.cn/problems/combinations/
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
    void backtracking(int n, int k, int startindex)
    {
        // base case
        if (path.size() == k)
        {
            result.push_back(path);
            return;
        }

        // 当前还需要 k-path.size()个元素才能凑够 k个
        // 还剩下 n+1-i个元素可以取
        for (int i = startindex; k - path.size() <= n + 1 -i; i++)
        {
            path.push_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k)
    {
        result.clear();
        path.clear();
        backtracking(n, k, 1);
        return result;
    }
};