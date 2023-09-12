/**
 * @file 22_03.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-12
 * 407 . 收集雨水 II
 * https://leetcode.cn/problems/trapping-rain-water-ii/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;


// 双指针 贪心 大根堆
class Solution
{
public:
    int dir_x[4] = {0, 0, 1, -1};
    int dir_y[4] = {1, -1, 0, 0};

    int trapRainWater(vector<vector<int>> &heightMap)
    {
        auto cmp = [&](const pair<int, int> &a, const pair<int, int> &b)
        {
            return heightMap[a.first][a.second] > heightMap[b.first][b.second];
        };

        int m = heightMap.size();
        int n = heightMap[0].size();

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // 把最外面一圈放进去
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                {
                    pq.push({i, j});
                    visited[i][j] = true;
                }
            }
        }

        // 小根堆每次更新容易漏的
        int water = 0;
        int max_min = 0;
        while (!pq.empty())
        {

            pair<int, int> cur = pq.top();
            pq.pop();
            max_min = max(heightMap[cur.first][cur.second], max_min);

            for (int j = 0; j < 4; j++)
            {
                int next_i = cur.first + dir_x[j];
                int next_j = cur.second + dir_y[j];

                if (next_i >= 0 && next_i < m && next_j >= 0 && next_j < n && !visited[next_i][next_j])
                {
                    visited[next_i][next_j] = true;
                    pq.push({next_i, next_j});
                    water += max(0, max_min - heightMap[next_i][next_j]);
                }
            }
        }
        return water;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<vector<int>> heightMap = {{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}};
    auto result = solution.trapRainWater(heightMap);
    cout << "result:" << result << endl;

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