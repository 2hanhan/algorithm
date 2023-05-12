/**
 * @file jump-game.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 55. 跳跃游戏
 * https://leetcode.cn/problems/jump-game/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;
class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int max = 0;
        for (int i = 0; i <= max; i++)
        {
            max = i + nums[i] > max ? i + nums[i] : max;

            if (max >= nums.size() - 1)
                return true;
        }
        return false;
    }
};