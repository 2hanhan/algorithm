/**
 * @file combination-sum-iv.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 377. 组合总和 Ⅳ
 * https://leetcode.cn/problems/combination-sum-iv/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <limits.h>
using namespace std;

class Solution
{
public:
    int combinationSum4(vector<int> &nums, int target)
    {

        vector<unsigned long long> DP(target + 1, 0);
        DP[0] = 1;

        for (int i = 0; i <= target; i++)
        {
            for (int j = 0; j < nums.size(); j++)
            {
                if (i - nums[j] >= 0)
                {
                    DP[i] += DP[i - nums[j]];
                }
            }
        }

        return DP[target];
    }
};