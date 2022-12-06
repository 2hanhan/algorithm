/**
 * @file binary-search.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-05
 * https://leetcode.cn/problems/binary-search/
 * @copyright Copyright (c) 2022
 * - 2. 二分查找
 * - 二分法差值
 * - 确定搜索区间        [left,right]        或者  [left,right)
 * - 起始条件           left = 0,right = n  或者  left = 0,right = -1
 * - 需要主要边界值的更新 left = middle + 1   或者  left = middle + 1
 * - 需要主要边界值的更新 right = middle - 1  或者  right = middle
 */

#include <iostream>
#include <vector>
using namespace std;

// class Solution
// {
// public:
//     int search(vector<int> &nums, int target)
//     {

//         int left = 0;
//         int right = nums.size() - 1;

//         while (left <= right)
//         {
//             int middle = (left + right) / 2;
//             if (nums[middle] < target)
//             {
//                 left = middle + 1;
//             }
//             else if (nums[middle] > target)
//             {
//                 right = middle - 1;
//             }
//             else if (nums[middle] == target)
//             {
//                 return middle;
//             }
//         }
//         return -1;
//     }
// };

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {

        int left = 0;
        int right = nums.size();

        while (left < right)
        {
            int middle = (left + right) / 2;
            if (nums[middle] < target)
            {
                left = middle + 1;
            }
            else if (nums[middle] > target)
            {
                right = middle;
            }
            else if (nums[middle] == target)
            {
                return middle;
            }
        }
        return -1;
    }
};

int main(int argc, char **argv)
{
    int n;
    cout << "输入数组数组大小 n" << std::endl;
    cin >> n;

    vector<int> nums(n);
    int target;
    cout << "依次从小到大输入n个数字作为查询列表" << std::endl;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    cout << "输入查询数字" << std::endl;
    cin >> target;

    Solution solution;

    std::cout << "数组:" << std::endl;
    for (int i = 0; i < n; i++)
    {
        cout << nums[i] << " ";
    }
    std::cout << endl
              << "查询目标:" << solution.search(nums, target) << std::endl;

    cout << "-----结束-----" << endl;
    return 0;
}