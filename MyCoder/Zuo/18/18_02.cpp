/**
 * @file 18_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-02
 * 934.最短的桥
 * https://leetcode.cn/problems/shortest-bridge/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>

using namespace std;


// 这个思路被讲解视频带偏了，其实只要bfs就可以了
class Solution
{
public:
    int dir_x[4] = {0, 0, 1, -1};
    int dir_y[4] = {1, -1, 0, 0};

    void land_bfs(vector<vector<int>> &map, int m, int n, int x, int y, vector<vector<pair<int, int>>> &lands)
    {
        if (map[x][y] != 1)
            return;

        vector<pair<int, int>> land;

        queue<pair<int, int>> path;
        path.push({x, y});
        map[x][y] = 2; // 处理过的设置为2
        land.push_back({x, y});

        while (!path.empty())
        {
            int size = path.size();
            for (int i = 0; i < size; i++)
            {
                pair<int, int> cur = path.front();
                path.pop();

                for (int j = 0; j < 4; j++)
                {
                    int next_x = cur.first + dir_x[j];
                    int next_y = cur.second + dir_y[j];
                    if (next_x >= 0 && next_x < m && next_y >= 0 && next_y < n)
                    {
                        if (map[next_x][next_y] == 1)
                        {
                            path.push({next_x, next_y});
                            map[next_x][next_y] = 2;
                            land.push_back({next_x, next_y});
                        }
                    }
                }
            }
        }

        lands.push_back(land);
    }

    void get_path_length(vector<vector<int>> &path, int m, int n, vector<pair<int, int>> land)
    {
        queue<pair<int, int>> visit;
        int dis = 1;

        for (int i = 0; i < land.size(); i++)
        {
            path[land[i].first][land[i].second] = 1;
            visit.push(land[i]);
        }

        while (!visit.empty())
        {
            int size = visit.size();
            dis++;
            for (int i = 0; i < size; i++)
            {
                pair<int, int> cur = visit.front();
                visit.pop();

                for (int j = 0; j < 4; j++)
                {
                    int next_x = cur.first + dir_x[j];
                    int next_y = cur.second + dir_y[j];
                    if (next_x >= 0 && next_x < m && next_y >= 0 && next_y < n)
                    {
                        if (path[next_x][next_y] == 0)
                        {
                            visit.push({next_x, next_y});
                            path[next_x][next_y] = dis;
                        }
                    }
                }
            }
        }
    }

    int shortestBridge(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<pair<int, int>>> lands;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                land_bfs(grid, m, n, i, j, lands);
            }
        }

        vector<vector<int>> path0(m, vector<int>(n, 0));
        vector<vector<int>> path1(m, vector<int>(n, 0));

        get_path_length(path0, m, n, lands[0]);
        get_path_length(path1, m, n, lands[1]);

        int path_length = INT_MAX;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // cout << i << "," << j << ":" << path0[i][j] << "+" << path1[i][j] << endl;
                path_length = min<int>(path0[i][j] + path1[i][j] - 3, path_length);
            }
        }

        return path_length;
    }
};

int main()
{

    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<vector<int>> grid = {{0, 1}, {1, 0}};
    auto result = solution.shortestBridge(grid);
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