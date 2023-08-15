/**
 * @file intersection-of-two-arrays.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-22
 * 4.3 两个数组的交集
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
#include <unordered_set>

using namespace std;

// 使用unorder_set
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        // 存放交集数字
        unordered_set<int> result_set;

        // 有nums1生成set
        unordered_set<int> nums_set(nums1.begin(), nums1.end());

        // 遍历nums2中的数获取交集
        for (int num : nums2)
        {
            if (nums_set.find(num) != nums_set.end())
                result_set.insert(num);
        }

        return vector<int>(result_set.begin(), result_set.end());
    }
};

// 使用数组求解
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        // 存放交集数字
        unordered_set<int> result_set;
        // 统计出现的数字
        int record[1001] = {0};

        for (int num : nums1)
        {
            record[num] = 1;
        }

        for (int num : nums2)
        {
            if (record[num] == 1)
                result_set.insert(num);
        }

        return vector<int>(result_set.begin(), result_set.end());
    }
};