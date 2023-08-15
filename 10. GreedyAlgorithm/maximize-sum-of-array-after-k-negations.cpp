/**
 * @file maximize-sum-of-array-after-k-negations.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 1005. K 次取反后最大化的数组和
 * https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        //排序
        sort(nums.begin(), nums.end());
        // 从最小的负数开始，到正数结束，或者i到头了
        int i = 0;
        while (k > 0 && i <nums.size())
        {
            if (nums[i] < 0)
            {
                nums[i] = -nums[i];
                k--;
                i++;
            }
            else
            {
                break;
            }
        }

        // k 还没用完，最小的正数*-1
        if (k % 2 != 0)
        {
            if (i - 1 >= 0 && nums[i] > nums[i - 1]||i == nums.size())
                nums[i - 1] = -nums[i - 1];
            else
                nums[i] = -nums[i];
        }

        //求和
        int result = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            result += nums[i];
        }

        return result;
    }
};