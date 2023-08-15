/**
 * @file 4sum-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-22
 * 4.6 四数相加II，数组1、2、3、4分别提供a、b、c、d
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4)
    {
        unordered_map<int, int> sum12; //<a+b的数值，a+b出现的次数>

        for (int num1 : nums1)
        {
            for (int num2 : nums2)
            {
                sum12[num1 + num2]++;
            }
        }

        int count = 0;
        for (int num3 : nums3)
        {
            for (int num4 : nums4)
            {
                auto iter = sum12.find(0 - num3 - num4);
                if (iter != sum12.end())   // c+d == -(a+b)
                    count += iter->second; // 统计计算a+b=c+d次数
            }
        }

        return count;
    }
};