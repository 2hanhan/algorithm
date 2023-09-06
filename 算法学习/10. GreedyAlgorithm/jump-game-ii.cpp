/**
 * @file jump-game-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 45. 跳跃游戏 II
 * https://leetcode.cn/problems/jump-game-ii/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
#include <sys/resource.h>
using namespace std;

class Solution0
{
public:
    int jump(vector<int> &nums)
    {
        vector<int> min(1, 0);
        int max = nums[0];
        int step = 0;
        int i = 0;

        while (i < nums.size() - 1)
        {
            step++;
            int nextmax = 0;
            while (i <= max)
            {
                nextmax = i + nums[i] > nextmax ? i + nums[i] : nextmax;
                i++;
            }
            if (nextmax >= nums.size())
                break;
            max = nextmax;
        }
        return step;
    }
};

// 贪心
class Solution
{
public:
    int jump(vector<int> &nums)
    {

        if (nums.size() <= 1)
            return 0;

        int max_pose = 0; // 当前能到达的最远距离
        int right = -1;   // 先前能到达的最远距离
        int step = -1;    // 当前步骤

        for (int i = 0; i < nums.size(); i++)
        {
            if (i > right)
            {
                step++;
                right = max_pose;
            }

            max_pose = max<int>(max_pose, i + nums[i]);

            if (max_pose >= nums.size() - 1)
                return step + 1;
        }
        return step;
    }
};

// bfs
class Solution
{
public:
    int jump(vector<int> &nums)
    {

        if (nums.size() <= 1)
            return 0;

        int max_pose = 0; // 当前能到达的最远距离
        int left = 0;     // 当前遍历到第个
        int right = 0;    // 先前能到达的最远距离
        int step = 0;     // 当前步骤

        while (left <= min<int>(max_pose, nums.size() - 1))
        {
            step++;
            while (left <= right)
            {
                max_pose = max<int>(left + nums[left], max_pose); // 更新当前能到达的最远距离
                if (max_pose >= nums.size() - 1)                  // 已经到达最后了
                {
                    return step;
                }
                left++;
            }
            right = max_pose; // 用当前的更新先前能到达的最远距离
        }
        return -1;
    }
};

// bfs
class Solution1
{
public:
    int jump(vector<int> &nums)
    {
        int step = 0;
        if (nums.size() <= 1)
            return 0;

        vector<bool> visited(nums.size(), false);

        queue<int> Q;
        Q.push(0);
        visited[0] = true;

        while (!Q.empty())
        {
            step++; // 记录当前步数
            int size = Q.size();
            for (int i = 0; i < size; i++)
            {
                int pose = Q.front();
                Q.pop();

                for (int j = 1; j <= nums[pose]; j++)
                {
                    int next_pose = pose + j;
                    if (next_pose >= nums.size() - 1) // 能够到达终止位置
                    {
                        return step;
                    }

                    if (!visited[next_pose])
                    {
                        Q.push(next_pose); // 所有步数为step的位置
                        visited[next_pose] = true;
                    }
                }
            }
        }
        return -1;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<int> nums = {1, 2, 1, 1, 1, 4, 4, 1, 5, 2, 3, 4, 1, 4, 2, 5, 2, 6, 4, 4, 2, 2, 5, 6, 2, 3, 4, 5, 4, 4, 2, 3, 1, 4, 1, 6, 2, 3, 5, 3, 6, 6, 1, 2, 5, 3, 3, 4, 6, 1, 1, 5, 3, 3, 4, 5, 1, 4, 2, 6, 6, 4, 1, 4, 1, 2, 1, 4, 4, 2, 1, 2, 2, 5, 6, 5, 4, 4, 3, 6, 5, 2, 5, 6, 1, 4, 3, 4, 3, 3, 1, 2, 6, 5, 3, 6, 1, 2, 6, 4, 2, 3, 3, 4, 6, 3, 5, 3, 2, 3, 3, 1, 3, 2, 4, 1, 3, 5, 1, 1, 5, 2, 4, 2, 2, 5, 3, 4, 2, 1, 3, 3, 1, 2, 4, 5, 4, 6, 2, 5, 6, 4, 6, 5, 2, 2, 1, 4, 6, 4, 2, 4, 1, 6, 3, 3, 6, 1, 4, 5, 4, 5, 1, 2, 3, 6, 1, 4, 3, 2, 5, 1, 5, 2, 5, 1, 2, 3, 3, 6, 6, 3, 5, 2, 6, 1, 6, 4, 3, 4, 1, 2, 5, 1, 5, 6, 5, 3, 1, 5, 6, 3, 6, 3, 5, 6, 2, 2, 6, 3, 4, 1, 4, 1, 1, 3, 4, 1, 5, 6, 5, 4, 2, 5, 3, 6, 4, 1, 2, 3, 5, 6, 5, 2, 3, 6, 1, 3, 4, 6, 3, 2, 5, 5, 1, 6, 6, 6, 2, 3, 5, 5, 4, 5, 2, 1, 6, 6, 2, 5, 1, 3, 2, 5, 1, 2, 3, 4, 1, 1, 5, 1, 4, 1, 2, 2, 6, 1, 4, 3, 2, 1, 6, 5, 1, 6, 2, 3, 5, 3, 6, 6, 5, 2, 1, 4, 4, 5, 3, 5, 5, 1, 3, 2, 6, 1, 6, 6, 4, 6, 5, 3, 3, 1, 6, 2, 6, 4, 2, 4, 1, 2, 2, 2, 2, 1, 5, 4, 3, 6, 3, 2, 5, 5, 4, 6, 4, 1, 5, 2, 4, 6, 2, 4, 5, 5, 3, 4, 6, 6, 1, 6, 6, 5, 3, 1, 4, 6, 5, 3, 5, 3, 5, 2, 3, 4, 6, 2, 5, 6, 6, 2, 5, 6, 1, 1, 5, 4, 5, 6, 6, 5, 5, 3, 3, 4, 4, 5, 2, 6, 5, 1, 3, 2, 3, 1, 3, 1, 2, 3, 5, 2, 5, 3, 2, 2, 3, 4, 4, 2, 6, 5, 1, 3, 4, 6, 1, 6, 4, 4, 2, 4, 5, 2, 5, 6, 6, 1, 3, 1, 1, 4, 6, 5, 6, 4, 1, 3, 1, 1, 6, 2, 6, 4, 5, 5, 3, 5, 3, 6, 6, 2, 1, 3, 2, 5, 5, 3, 5, 3, 3, 5, 3, 2, 1, 2, 2, 6, 1, 6, 4, 2, 2, 2, 6, 2, 4, 2, 5, 5, 2, 3, 1, 1, 5, 6, 6, 3, 4, 6, 2, 1, 2, 1, 4, 2, 5, 6, 5, 5, 3, 2, 1, 5, 1, 3, 2, 2, 5, 1, 6, 1, 6, 5, 6, 2, 6, 3, 6, 5, 1, 4, 6, 3, 3, 6, 6, 4, 1, 4, 6, 3, 4, 1, 4, 2, 5, 5, 5, 4, 2, 5, 6, 6, 3, 1, 5, 4, 2, 3, 6, 1, 6, 4, 1, 5, 5, 6, 4, 5, 4, 4, 6, 5, 2, 5, 1, 4, 3, 2, 6, 1, 5, 2, 6, 2, 6, 1, 2, 3, 5, 5, 4, 4, 5, 4, 2, 1, 4, 1, 4, 6, 1, 1, 2, 6, 2, 3, 6, 4, 4, 5, 6, 6, 4, 1, 6, 3, 2, 4, 1, 4, 5, 5, 2, 6, 6, 4, 2, 5, 4, 6, 6, 5, 2, 4, 1, 1, 4, 1, 1, 4, 6, 1, 5, 2, 4, 6, 5, 1, 6, 6, 6, 2, 1, 6, 1, 5, 5, 4, 5, 2, 3, 2, 2, 2, 6, 4, 6, 2, 4, 6, 4, 5, 1, 3, 2, 4, 2, 6, 6, 4, 3, 3, 1, 1, 4, 4, 5, 5, 4, 1, 6, 5, 1, 3, 3, 6, 5, 5, 3, 6, 3, 5, 2, 4, 3, 4, 6, 5, 2, 6, 6, 1, 2, 3, 4, 6, 1, 5, 6, 4, 6, 6, 1, 1, 2, 4, 6, 4, 1, 1, 6, 6, 2, 1, 1, 2, 3, 6, 5, 3, 1, 6, 1, 3, 6, 2, 4, 5, 3, 2, 5, 3, 5, 5, 2, 1, 3, 4, 4, 6, 2, 4, 3, 3, 1, 5, 3, 3, 1, 2, 5, 2, 5, 2, 2, 4, 2, 2, 4, 6, 3, 1, 4, 2, 3, 4, 2, 2, 6, 3, 2, 6, 3, 3, 5, 5, 5, 2, 3, 1, 6, 5, 4, 5, 2, 6, 5, 2, 1, 2, 2, 2, 2, 2, 3, 2, 6, 3, 1, 5, 6, 1, 4, 6, 5, 3, 3, 5, 5, 6, 5, 1, 4, 3, 5, 5, 3, 4, 6, 4, 6, 3, 2, 1, 1, 6, 2, 2, 5, 5, 3, 1, 3, 5, 6, 3, 6, 2, 5, 6, 2, 1, 4, 4, 2, 2, 6, 2, 1, 5, 6, 1, 1, 3, 3, 5, 5, 3, 2, 5, 2, 1, 3, 2, 4, 3, 5, 2, 5, 5, 4, 1, 1, 3, 4, 3, 1, 3, 5, 5, 4, 5, 5, 1, 3, 5, 4, 6, 5, 4, 2, 1, 2, 6, 6, 4, 4, 5, 6, 6, 6, 3, 4, 3, 5, 2, 5, 6, 5, 2, 1, 4, 5, 3, 1, 6, 4, 1, 5, 4, 5, 2, 5, 1, 4, 2, 6, 3, 3, 5, 1, 3, 4, 3, 3, 6, 6, 5, 5, 5, 4, 5, 3, 6, 6, 6, 4, 2, 4, 4, 1, 2, 2, 2, 3, 2, 2, 5, 6, 5, 6, 3, 3, 1, 1, 4, 1, 6, 6, 5, 3, 2, 6, 5, 2, 1, 6, 1, 4, 6, 4, 1, 2, 1, 2, 5, 1, 1, 6, 3, 2, 5, 4, 5, 2, 6, 5, 6, 2, 2, 1, 5, 5, 1, 6, 2, 1, 3, 4, 5, 4, 3, 1, 5, 6, 5, 4, 1, 2, 3, 4, 2, 2, 6, 2, 4, 3, 2, 5, 3, 2, 2, 5, 6, 3, 3, 2, 1, 4, 5, 2, 3, 2, 5, 3, 1, 3, 6, 3, 6, 4, 2, 5, 3, 6, 1, 6, 5, 2, 1, 5, 2, 1, 1, 4, 3, 3, 1, 1, 2, 2, 1, 1, 4, 1, 6, 5, 5, 6, 4, 6, 6, 2, 2, 2, 6, 1, 1, 1, 1, 5, 2, 2, 1, 6, 5, 6, 1, 3, 1, 6, 4, 1, 2, 1, 5, 1, 1, 3, 6, 4, 5, 4, 2, 3, 4, 1, 5, 2, 2, 1, 6, 2, 3, 2, 3, 3, 1, 1, 4, 5, 5, 3, 5, 3, 6, 4, 5, 4, 4, 4, 2, 2, 1, 4, 6, 0, 0, 0, 0, 0};
    cout << "result:" << solution.jump(nums) << endl;

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
