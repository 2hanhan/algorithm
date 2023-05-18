/**
 * @file minimum-size-subarray-sum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-05
 * 209. 长度最小的子数组
 * https://leetcode.cn/problems/minimum-size-subarray-sum/
 * - 长度最小的子数组
 * - j是划窗右端点，for循环变量j
 * - i是划窗左端点，每次判断是否更新minnums
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int minnums = nums.size() + 1;
        int i = 0, j = 0, sum = 0;
        for (; j < nums.size(); j++)
        {
            sum += nums[j];
            while (sum >= target)
            {
                if (j - i + 1 < minnums)
                    minnums = j - i + 1;
                sum -= nums[i];
                i++;
            }
        }
        return minnums == nums.size() + 1 ? 0 : minnums;
    }
};

int main(int argc, char **argv)
{
    int n;
    cout << "输入数组数组大小 n" << std::endl;
    cin >> n;

    vector<int> nums(n);
    int target;
    cout << "输入n个正整数作为输入" << std::endl;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    cout << "输入数组和" << endl;
    cin >> target;

    Solution solution;
    int minnums = solution.minSubArrayLen(target, nums);

    cout << "输入数组:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << nums[i] << " ";
    }

    cout << endl
         << "最短数组长度:" << endl
         << minnums << endl;

    cout <<"-----结束-----"<< endl;
     return 0;
}