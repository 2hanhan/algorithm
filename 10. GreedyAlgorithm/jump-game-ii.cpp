/**
 * @file jump-game-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 45. 跳跃游戏 II
 * https://leetcode.cn/problems/jump-game-ii/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        vector<int> min(1, 0);
        int max = nums[0];
        int step = 0;
        int i = 0;
        while (i < nums.size() - 1)
        {
            step++;
            int nextmax = 0;
            while (i <= max)
            {
                nextmax = i + nums[i] > nextmax ? i + nums[i] : nextmax;
                i++;
            }
            if (nextmax >= nums.size())
                break;
            max = nextmax;
        }
        return step;
    }
};