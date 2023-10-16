/**
 * @file sudoku-solver.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 37. 解数独
 * https://leetcode.cn/problems/sudoku-solver/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
using namespace std;

class Solution
{
public:
    bool isValid(vector<vector<char>> &board, int i, int j) // 判断新增后是否合理
    {
        for (int k = 0; k < 9; k++)
        {
            if (k == i)
                continue;
            if (board[k][j] == board[i][j])
                return false;
        }
        for (int k = 0; k < 9; k++)
        {
            if (k == j)
                continue;
            if (board[i][k] == board[i][j])
                return false;
        }
        int startRow = (i / 3) * 3;
        int startCol = (j / 3) * 3;
        for (int row = startRow; row < startRow + 3; row++)
        {
            for (int col = startCol; col < startCol + 3; col++)
            {
                if (row == i && col == j)
                    continue;
                if (board[i][j] == board[row][col])
                    return false;
            }
        }

        return true;
    }

    
    bool backTracking(vector<vector<char>> &board, int i, int j)
    {
        // base case
        int x = i * 9 + j + 1;
        if (x >= 82)
            return true; // 如果填到了82个则填满了，结束

        if (board[i][j] == '.')
        {
            for (char k = '1'; k <= '9'; k++)
            {
                board[i][j] = k;
                if (isValid(board, i, j))
                {
                    if (backTracking(board, x / 9, x % 9)) // 填下一个
                        return true;
                }
                board[i][j] = '.';
            }
            return false;
        }
        else
        {
            return backTracking(board, x / 9, x % 9); // 填下一个
        }
    }
    void solveSudoku(vector<vector<char>> &board)
    {
        backTracking(board, 0, 0);
    }
};