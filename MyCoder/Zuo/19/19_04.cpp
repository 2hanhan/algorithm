/**
 * @file 19_04.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-07
 * 632. K 列表中的最小范围覆盖元素
 * https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> smallestRange(vector<vector<int>> &nums)
    {
        int left = -100000;
        int right = 100000;

        // 记录第x行的下一个
        int size = nums.size();
        vector<int> next(size, 0);

        auto cmp = [&](const int &a, const int &b)
        { return nums[a][next[a]] > nums[b][next[b]]; };

        cout << "cmp:" << typeid(cmp).name() << endl;
        

        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

        int min_value = 100000;
        int max_value = -100000;

        for (size_t i = 0; i < size; i++)
        {
            pq.push(i);
            max_value = max(max_value, nums[i][0]);
        }

        while (1)
        {
            // 弹出最小的行号
            int x = pq.top();
            pq.pop();
            // 取最小的行的下一个
            min_value = nums[x][next[x]];

            if (max_value - min_value < right - left)
            {
                left = min_value;
                right = max_value;
            }

            // 如果有任意一行用完了则结束
            if (next[x] + 1 == nums[x].size())
            {
                break;
            }

            // 放入x这一行的next[x]位置的新元素进来，并更新最大范围
            next[x]++;
            pq.emplace(x);
            max_value = max(max_value, nums[x][next[x]]);
        }

        return {left, right};
    }
};

// 有序表 multimap超时
class Solution1
{
public:
    vector<int> smallestRange(vector<vector<int>> &nums)
    {
        vector<int> result(2);
        multimap<int, pair<int, int>> myMap;

        for (size_t i = 0; i < nums.size(); i++)
        {
            pair<int, int> xy = {i, 0};
            myMap.insert(make_pair(nums[i][0], xy));
        }

        auto max_xy = max_element(myMap.begin(), myMap.end());
        auto min_xy = min_element(myMap.begin(), myMap.end());

        int left = nums[min_xy->second.first][min_xy->second.second];
        int right = nums[max_xy->second.first][max_xy->second.second];

        result[0] = left;
        result[1] = right;
        int min_length = right - left;

        while (min_xy->second.second + 1 < nums[min_xy->second.first].size())
        {
            // 弹出最小的
            int pose = min_xy->second.first;
            int index = min_xy->second.second + 1;
            pair<int, int> xy = {pose, index};
            myMap.erase(min_xy);

            myMap.insert(make_pair(nums[pose][index], xy));

            max_xy = max_element(myMap.begin(), myMap.end());
            min_xy = min_element(myMap.begin(), myMap.end());

            left = nums[min_xy->second.first][min_xy->second.second];
            right = nums[max_xy->second.first][max_xy->second.second];

            if (min_length > right - left)
            {
                result[0] = left;
                result[1] = right;
                min_length = right - left;
            }
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
    // vector<vector<int>> nums = {{4, 10, 15, 24, 26}, {0, 9, 12, 20}, {5, 18, 22, 30}};

    vector<vector<int>> nums = {{-89, 1, 69, 89, 90, 98},
                                {-43, -36, -24, -14, 49, 61, 66, 69},
                                {73, 94, 94, 96},
                                {11, 13, 76, 79, 90},
                                {-40, -20, 1, 9, 12, 12, 14},
                                {-91, -31, 0, 21, 25, 26, 28, 29, 29, 30},
                                {23, 88, 89},
                                {31, 42, 42, 57},
                                {-2, 6, 11, 12, 12, 13, 15},
                                {-3, 25, 34, 36, 39},
                                {-7, 3, 29, 29, 31, 32, 33},
                                {4, 11, 14, 15, 15, 18, 19},
                                {-34, 9, 12, 19, 19, 19, 19, 20},
                                {-26, 4, 47, 53, 64, 64, 64, 64, 64, 65},
                                {-51, -25, 36, 38, 50, 54},
                                {17, 25, 38, 38, 38, 38, 40},
                                {-30, 12, 15, 19, 19, 20, 22},
                                {-14, -13, -10, 68, 69, 69, 72, 74, 75},
                                {-39, 42, 70, 70, 70, 71, 72, 72, 73},
                                {-67, -34, 6, 26, 28, 28, 28, 28, 29, 30, 31}};
    auto result = solution.smallestRange(nums);
    cout << "result:[" << result[0] << "," << result[1] << "]" << endl;

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