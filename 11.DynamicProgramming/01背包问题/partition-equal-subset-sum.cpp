/**
 * @file partition-equal-subset-sum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 416. 分割等和子集
 * https://leetcode.cn/problems/partition-equal-subset-sum/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        // 求和
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
            sum += nums[i];
        if (sum % 2 == 0)
            sum = sum >> 1;
        else
            return false;

        // 初始化
        vector<int> DP(sum + 1, 0);
        // 滚动式填充一维数组
        for (int i = 0; i < nums.size(); i++)
        {
            //尝试累加nums[i]
            for (int j = sum; j >= nums[i]; j--)
            {
                int cursum1 = nums[i] + DP[j - nums[i]];
                int cursum2 = DP[j];
                DP[j] = cursum1 > cursum2 ? cursum1 : cursum2;
                if (DP[j] == sum)
                    return true;
            }
        }
        return false;
    }
};