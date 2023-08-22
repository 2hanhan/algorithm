/**
 * @file longest-increasing-subsequence.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 300. 最长递增子序列
 * https://leetcode.cn/problems/longest-increasing-subsequence/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 动态规划
// 时间复杂度O(n^2)
class Solution0
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int size = nums.size();
        if (size <= 0)
            return size;
        int result = 0;
        vector<int> dp(size, 1); // 以i位置结尾的最长递增子序列
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                    dp[i] = max(dp[j] + 1, dp[i]); // 以nums[i]结尾的最大的长度
            }
            if (dp[i] > result)
                result = dp[i];
        }
        return result;
    }
};

// 动态规划
// 时间复杂度O(n*logn)
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int size = nums.size();
        if (size <= 0)
            return size;

        // 子序列长度为left+1的最小的结尾数组为end[left];
        vector<int> end(1, nums[0]);
        // 目前遍历完成nums[i]，结尾为nums[i]的子序列的的最长的长度为left+1
        for (int i = 1; i < size; i++)
        {
            int end_size = end.size();

            // 二分查找nums[i]放置位置left，nums[i]、end[left]取最小的
            int left = 0, right = end_size - 1;
            while (left <= right)
            {
                int mid = (left + right) >> 1;
                if (nums[i] > end[mid])
                {
                    left = mid + 1; // 大于则继续移动left位置
                }
                else
                {
                    right = mid - 1;
                }
            }

            // 在end的left位置放置数字nums[i]或者end[left]中最小的
            if (left == end_size)
            {
                end.push_back(nums[i]);
            }
            else if (left < 0)
            {
                end[0] = min(nums[i], end[left]);
            }
            else
            {
                end[left] = min(nums[i], end[left]);
            }
            // cout << left << ":" << end[left] << "result:" << end.size() << endl;
        }
        return end.size();
    }
};

int main()
{
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    Solution solution;

    cout << " result:" << solution.lengthOfLIS(nums) << endl;
}