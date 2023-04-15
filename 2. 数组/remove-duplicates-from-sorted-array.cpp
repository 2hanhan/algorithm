/**
 * @file remove-duplicates-from-sorted-array.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-13
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-array/
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        //起始位置从 0 ，1开始
        //双指针方法
        int p1 = 0;
        int p2 = 1;
        while (p2 < nums.size())
        {
            if (nums[p2] == nums[p1])
            {
                p2++;
            }
            else
            {
                nums[++p1] = nums[p2++];
            }
        }
        return p1 + 1;
    }
};