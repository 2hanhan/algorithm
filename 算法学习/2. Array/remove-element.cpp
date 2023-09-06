/**
 * @file remove-element.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-05
 * 27. 移除元素
 * https://leetcode.cn/problems/remove-element/
 * - 双指针移除制定元素
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int j = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != val)
            {
                nums[j] = nums[i];
                j++;
            }
        }
        nums.resize(j);
        return j;
    }
};

int main(int argc, char **argv)
{
    int n;
    cout << "输入数组数组大小 n" << std::endl;
    cin >> n;

    vector<int> nums(n);
    int val;
    cout << "输入n个数字作为原数组" << std::endl;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    cout << "输入删除数字" << std::endl;
    cin >> val;

    Solution solution;

    std::cout << "原来数组:" << std::endl;
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    std::cout << endl
              << "新的数组大小:" << solution.removeElement(nums, val) << std::endl;
    std::cout << "新的数组:" << std::endl;
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    std::cout << std::endl;

    cout << "-----结束-----" << endl;
    return 0;
}