/**
 * @file median-of-two-sorted-arrays.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-16
 * 4.寻找两个正序数组的中位数
 * https://leetcode.cn/problems/median-of-two-sorted-arrays
 * @copyright Copyright (c) 2023
 *
 */
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int getKthElement(const vector<int> &nums1, const vector<int> &nums2, int k)
    {
        // nums1区间[left1,m)
        // nums2区间[left2,n)
        // 两个区间中从小到大的第k个数
        int m = nums1.size();
        int n = nums2.size();
        int left1 = 0, left2 = 0;

        while (true)
        {

            // 删除元素，直至k=1或者，有一个nums被删除完了
            if (left1 == m)
            {
                return nums2[left2 + k - 1];
            }
            if (left2 == n)
            {
                return nums1[left1 + k - 1];
            }
            if (k == 1)
            {
                return min(nums1[left1], nums2[left2]);
            }

            int left1_new = min<int>(left1 + k / 2 - 1, m - 1);
            int left2_new = min<int>(left2 + k / 2 - 1, n - 1);
            int p1 = nums1[left1_new];
            int p2 = nums2[left2_new];

            if (p1 <= p2)
            {
                // 还剩多少个k
                k -= left1_new - left1 + 1;
                // 从p1中删除元素
                left1 = left1_new + 1;
            }
            else
            {
                // 还剩多少个k
                k -= left2_new - left2 + 1;
                // 从p1中删除元素
                left2 = left2_new + 1;
            }
        }
    }

    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int length = nums1.size() + nums2.size();

        if (length % 2 == 1) // 奇数
        {
            int k = (length + 1) / 2;
            return getKthElement(nums1, nums2, k);
        }
        else
        {
            int k = length / 2;
            return (getKthElement(nums1, nums2, k) + getKthElement(nums1, nums2, k + 1)) / 2.0;
        }
    }
};

class Solution0
{
public:
    int getKthElement(const vector<int> &nums1, const vector<int> &nums2, int k)
    {
        // nums1区间[index1,m)
        // nums2区间[index2,n)
        // 两个区间中从小到大的第k个数
        int m = nums1.size();
        int n = nums2.size();
        int index1 = 0, index2 = 0;

        while (true)
        {
            // 边界情况
            if (index1 == m)
            {
                return nums2[index2 + k - 1]; // nums1区间没有数了，只能从nums2中取数
            }
            if (index2 == n)
            {
                return nums1[index1 + k - 1]; // nums2区间没有数了，只能从nums1中取数
            }
            if (k == 1) // 需要取k = 1个数则取最小的
            {
                return min(nums1[index1], nums2[index2]);
            }

            // 正常情况
            int newIndex1 = min(index1 + k / 2 - 1, m - 1);
            int newIndex2 = min(index2 + k / 2 - 1, n - 1);
            int pivot1 = nums1[newIndex1];
            int pivot2 = nums2[newIndex2];
            // 把最小的k/2-1个数删除
            if (pivot1 <= pivot2)
            {
                k -= newIndex1 - index1 + 1;
                index1 = newIndex1 + 1;
            }
            else
            {
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }
        }
    }

    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int totalLength = nums1.size() + nums2.size();
        if (totalLength % 2 == 1)
        {
            return getKthElement(nums1, nums2, (totalLength + 1) / 2);
        }
        else
        {
            return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }
};

int main()
{
    vector<int> nums1 = {1, 2};
    vector<int> nums2 = {3, 4};
    Solution solution;
    cout << solution.findMedianSortedArrays(nums1, nums2) << endl; // 输出：5
    return 0;
}