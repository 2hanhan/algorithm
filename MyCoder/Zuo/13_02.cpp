/**
 * @file 13_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-21
 * 517. 超级洗衣机
 * https://leetcode.cn/problems/super-washing-machines/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 贪心算法
// 有单个位置的决策信息，觉得整体的决策信息
class Solution
{
public:
    int findMinMoves(vector<int> &machines)
    {
        int size = machines.size();
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += machines[i];
        }
        if (sum % size != 0)
            return -1;
        int mean = sum / size;
        int position_max = 0;

        int sum_left = 0;
        int sum_right;
        for (int i = 0; i < machines.size(); i++)
        {
            sum_right = sum - sum_left - machines[i];

            int move_to_right = sum_left - i * mean;
            int move_to_left = sum_right - (size - 1 - i) * mean;

            if (move_to_right < 0 && move_to_left < 0)
            {
                position_max = max<int>(position_max, -move_to_right - move_to_left);
            }
            else
            {
                position_max = max<int>(position_max, max<int>(abs(move_to_right), abs(move_to_left)));
            }

            sum_left += machines[i];
        }
        return position_max;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<int> nums;
    cout << "result:" << solution.findMinMoves(nums) << endl;

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