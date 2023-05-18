/**
 * @file ones-and-zeroes.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 474. 一和零
 * https://leetcode.cn/problems/ones-and-zeroes/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        vector<vector<int>> DP(m + 1, vector<int>(n + 1, 0));

        for (string str : strs)
        {
            int num0 = 0;
            int num1 = 0;
            for (char c : str)
            {
                if (c == '0')
                    num0++;
                else
                    num1++;
            }
            for (int i = m; i >= num0; i--)
            {
                for (int j = n; j >= num1; j--)
                {
                    DP[i][j] = max(DP[i - num0][j - num1] + 1, DP[i][j]);
                }
            }
        }

        return DP[m][n];
    }
};