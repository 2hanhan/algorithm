/**
 * @file majority-element-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-13
 * 229. 多数元素 II
 * https://leetcode.cn/problems/majority-element-ii/description/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 贪心
class Solution
{
public:
    vector<int> majorityElement(vector<int> &nums)
    {
        int n = 3;
        unordered_map<int, int> count;

        for (int i = 0; i < nums.size(); i++)
        {
            count[nums[i]]++;
            if (count.size() > n)
            {
                auto it = count.begin();
                while (it != count.end())
                {
                    it->second--;
                    if (it->second <= 0)
                    {
                        count.erase(it++);
                    }
                    else
                    {
                        it++;
                    }
                }
            }
        }

        auto it = count.begin();
        while (it != count.end())
        {
            // cout << it->first << ":" << it->second << endl;
            it->second = 0;
            it++;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (count.find(nums[i]) != count.end())
            {
                count[nums[i]]++;
            }
        }

        vector<int> result;
        it = count.begin();
        while (it != count.end())
        {
            // cout << it->first << ":" << it->second << endl;
            if (it->second > nums.size() / n)
                result.push_back(it->first);
            it++;
        }

        return result;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<int> nums = {3, 2, 3};
    auto result = solution.majorityElement(nums);
    cout << "result:" << endl;

    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;

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