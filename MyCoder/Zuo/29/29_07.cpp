/**
 * @file 29_07.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-16
 * 73. 矩阵置零
 * https://leetcode.cn/problems/set-matrix-zeroes/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        bool set_zero = false;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (matrix[i][j] == 0)
                {
                    if (j == 0)
                    {
                        set_zero = true;
                    }
                    else
                    {
                        matrix[0][j] = 0; // 列需要置零
                    }
                    matrix[i][0] = 0; // 行需要置零
                }
            }
        }

        // 置零,从最后一行开始，因为从第一行开始会导致后续列的置零出错
        for (int i = matrix.size() - 1; i >= 0; i--)
        {
            for (int j = 1; j < matrix[0].size(); j++)
            {
                if (matrix[0][j] == 0 || matrix[i][0] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        if (set_zero)
        {
            for (int i = 0; i < matrix.size(); i++)
            {
                matrix[i][0] = 0;
            }
        }
    }
};