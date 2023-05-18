/**
 * @file unique-paths-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-15
 * 63. 不同路径 II
 * https://leetcode.cn/problems/unique-paths-ii/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        vector<vector<int>> DP(m, vector<int>(n, 0));

        // 初始化
        for (int i = 0; i < m; i++)
        {
            if (obstacleGrid[i][0] == 1)
                break;
            DP[i][0] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            if (obstacleGrid[0][i] == 1)
                break;
            DP[0][i] = 1;
        }

        //填充DP
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (obstacleGrid[i][j] == 1)
                    DP[i][j] == 0;
                else
                    DP[i][j] = DP[i - 1][j] + DP[i][j - 1];
            }
        }
        return DP[m - 1][n - 1];
    }
};