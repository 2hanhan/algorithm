/**
 * @file number-of-islands.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-18
 * 1020. 飞地的数量
 * https://leetcode.cn/problems/number-of-enclaves/description/
 * @copyright Copyright (c) 2023
 *
 */

#include <queue>
#include <vector>
using namespace std;

// 广度优先搜索
class Solution
{
public:
    int count = 0;
    int direction[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    void bfs(vector<vector<int>> &grid, int x, int y)
    {
        // 广度优先搜索
        queue<pair<int, int>> que;
        que.push({x, y});
        grid[x][y] = 0; // 起点当前位置以及搜索过
        count++;
        while (!que.empty())
        {
            pair<int, int> current = que.front();
            que.pop();

            int current_x = current.first;
            int current_y = current.second;

            for (int i = 0; i < 4; i++)
            {
                // 找四周的
                int next_x = current_x + direction[i][0];
                int next_y = current_y + direction[i][1];

                if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size())
                {
                    continue;
                }
                if (grid[next_x][next_y] == 1) // 四周符合条件的
                {
                    que.push({next_x, next_y}); // 放进来
                    count++;                    // 计数当前的起点共合并了多少个
                    grid[next_x][next_y] = 0;   // 搜索过了
                }
            }
        }
    }

    int numEnclaves(vector<vector<int>> &grid)
    {
        int max_x = grid.size();
        int max_y = grid[0].size();

        // 靠近周围的一圈的
        for (int i = 0; i < max_x; i++)
        {
            if (grid[i][0] == 1)
            {
                bfs(grid, i, 0);
            }
            if (grid[i][max_y - 1] == 1)
            {
                bfs(grid, i, max_y - 1);
            }
        }

        for (int j = 0; j < max_y; j++)
        {
            if (grid[0][j] == 1)
            {
                bfs(grid, 0, j);
            }
            if (grid[max_x - 1][j] == 1)
            {
                bfs(grid, max_x - 1, j);
            }
        }

        // 重新计算不靠近周围一圈的个数
        count = 0;
        for (int i = 0; i < max_x; i++)
        {
            for (int j = 0; j < max_y; j++)
            {
                if (grid[i][j] == 1)
                {
                    bfs(grid, i, j);
                }
            }
        }

        return count;
    }
};