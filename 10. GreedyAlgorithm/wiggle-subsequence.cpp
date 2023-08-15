/**
 * @file wiggle-subsequence.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 376. 摆动序列
 * https://leetcode.cn/problems/wiggle-subsequence/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

class Solution
{
public:
    int wiggleMaxLength(vector<int> &nums)
    {
        int result = 0;
        int pre = 2;
        int now = 0;
        for (int i = 0; i < nums.size() - 1; i++)
        {

            if (nums[i] > nums[i + 1]) // 导数为正
                now = 1;
            else if (nums[i] == nums[i + 1]) // 导数为0，取之前的导数
                now = pre;
            else // 导数为负数
                now = -1;

            if (now * pre == -1) // 统计导数过0点
                result++;
            pre = now;
        }
        if (pre == 2) // 导数全部为0
            return 1;

        return result + 2; //导数不全为0
    }
};