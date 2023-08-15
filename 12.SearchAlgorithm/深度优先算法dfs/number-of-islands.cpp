/**
 * @file number-of-islands.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-18
 * 200.岛屿数量
 * https://leetcode.cn/problems/number-of-islands/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;

// 深度优先搜索
class Solution
{
public:
    int direction[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    void dfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, int x, int y)
    {
        for (int i = 0; i < 4; i++)
        {
            int next_x = x + direction[i][0];
            int next_y = y + direction[i][1];

            if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size())
            {
                continue;
            }

            if (!visited[next_x][next_y] && grid[next_x][next_y] == '1')
            {
                visited[next_x][next_y] = true;
                dfs(grid, visited, next_x, next_y);
            }
        }
    }

    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int result = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!visited[i][j] && grid[i][j] == '1')
                {
                    visited[i][j] = true;
                    result++;  
                    dfs(grid,visited,i,j);
                }
            }
        }
        return result;
    }
};