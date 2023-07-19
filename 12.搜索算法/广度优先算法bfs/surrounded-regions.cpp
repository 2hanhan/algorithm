/**
 * @file surrounded-regions.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-19
 * 130.被围绕的区域
 * https://leetcode.cn/problems/surrounded-regions/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    int direction[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
    void bfs(vector<vector<char>> &board, int x, int y, const char &from, const char &to)
    {
        // base case
        if (board[x][y] != from)
        {
            return;
        }
        else
        {
            board[x][y] = to;
        }

        queue<pair<int, int>> que;
        que.push({x, y});
        while (!que.empty())
        {

            int current_x = que.front().first;
            int current_y = que.front().second;
            que.pop();

            for (int i = 0; i < 4; i++)
            {
                int next_x = current_x + direction[i][0];
                int next_y = current_y + direction[i][1];

                if (next_x < 0 || next_x > board.size() - 1 || next_y < 0 || next_y > board[0].size() - 1)
                {
                    continue;
                }

                if (board[next_x][next_y] == from)
                {
                    board[next_x][next_y] = to;
                    que.push({next_x, next_y});
                }
            }
        }
    }

    void solve(vector<vector<char>> &board)
    {
        int max_x = board.size();
        int max_y = board[0].size();

        // step 1 把边界上的字符替换O=>1
        for (int i = 0; i < max_x; i++)
        {
            bfs(board, i, 0, 'O', '1');
            bfs(board, i, max_y - 1, 'O', '1');
        }

        for (int i = 0; i < max_y; i++)
        {
            bfs(board, 0, i, 'O', '1');
            bfs(board, max_x - 1, i, 'O', '1');
        }

        // step 2 处理剩下的非边界的O=>X
        for (int i = 0; i < max_x; i++)
        {
            for (int j = 0; j < max_y; j++)
            {
                bfs(board, i, j, 'O', 'X');
            }
        }

        // step 3 把边界上的字符替换1=>O
        for (int i = 0; i < max_x; i++)
        {
            bfs(board, i, 0, '1', 'O');
            bfs(board, i, max_y - 1, '1', 'O');
        }

        for (int i = 0; i < max_y; i++)
        {
            bfs(board, 0, i, '1', 'O');
            bfs(board, max_x - 1, i, '1', 'O');
        }
    }
};