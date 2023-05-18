/**
 * @file palindromic-substrings.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 647. 回文子串
 * https://leetcode.cn/problems/palindromic-substrings/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int countSubstrings(string s)
    {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));

        int result = 0;

        for (int i = s.size() - 1; i >= 0; i--)
        {
            for (int j = i; j < s.size(); j++)
            {
                if (i + 1 >= j)
                    dp[i][j] = s[i] == s[j];
                else
                    dp[i][j] = dp[i + 1][j - 1] && s[i] == s[j];

                if (dp[i][j])
                    result++;
            }
        }
        return result;
    }
};