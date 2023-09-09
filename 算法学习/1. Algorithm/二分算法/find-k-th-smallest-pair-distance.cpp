/**
 * @file find-k-th-smallest-pair-distance.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-09
 * 719. 找出第 K 小的数对距离
 * https://leetcode.cn/problems/find-k-th-smallest-pair-distance/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 二分法
class Solution
{
public:
    bool can(const vector<int> &nums, const int &k, const int &m)
    {
        int count = 0;
        // 滑动窗口求小于k的对数，时间复杂度O(N)
        for (int l = 0, r = 0; l < nums.size(); l++)
        {
            while (r + 1 < nums.size() && nums[r + 1] - nums[l] <= m)
            {
                r++;
            }
            count += r - l; // 以i开始到以r结束的区间共有r-i对
        }
        return count >= k;
    }

    int smallestDistancePair(vector<int> &nums, int k)
    {
        // 首先排序，时间复杂度O(NlongN)
        sort(nums.begin(), nums.end(), [](const int &a, const int &b)
             { return a < b; });

        int l = 0;
        int r = nums[nums.size() - 1] - nums[0];
        int ans;

        // 二分法，时间复杂度O(longN)
        // 二分法每次调用滑窗，时间复杂度O(NlongN)
        while (l <= r)
        {
            int m = l + ((r - l) >> 1);
            if (can(nums, k, m))
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        // 整个过程时间复杂度O(NlongN)
        return ans;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<int> nums = {1, 6, 1};
    int k = 3;
    auto result = solution.smallestDistancePair(nums, k);
    cout << "result:" << result << endl;

    // 结束计时
    auto end = std::chrono::high_resolution_clock::now();

    // 计算耗时
    std::chrono::duration<double> duration = end - start;
    double seconds = 1000 * duration.count();

    // 输出结果
    std::cout << endl;
    std::cout << "Elapsed time: " << std::fixed << std::setprecision(2) << seconds << " ms\n";

    return 0;
}