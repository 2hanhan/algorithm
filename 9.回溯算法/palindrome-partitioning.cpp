/**
 * @file palindrome-partitioning.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 131. 分割回文串
 * https://leetcode.cn/problems/palindrome-partitioning/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <string>
using namespace std;
class Solution
{
public:
    vector<vector<bool>> isPalindrome;
    vector<vector<string>> result;
    vector<string> path;
    void backTracking(string &s, int startIndex)
    {
        if (startIndex >= s.size())
        {
            result.push_back(path);
            return;
        }

        for (int i = startIndex; i < s.size(); i++)
        {
            if (isPalindrome[startIndex][i])
            {
                string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
                backTracking(s, i + 1);
                path.pop_back();
            }
        }
    }
    void computePalindrome(string &s)
    {
        isPalindrome.resize(s.size(), vector<bool>(s.size(), false));

        // 遍历填表
        // for (int i = 0; i < s.size(); i++)
        // {
        //     for (int j = i; j < s.size(); j++)
        //     {
        //         int left = i;
        //         int right = j;
        //         bool oneIsPalindrome = true;
        //         while (left < right)
        //         {
        //             if (s[left++] != s[right--])
        //             {
        //                 oneIsPalindrome = false;
        //                 break;
        //             }
        //         }
        //         isPalindrome[i][j] = oneIsPalindrome;
        //     }
        // }
        // 动态规划填表
        for (int i = s.size() - 1; i >= 0; i--)
        {
            for (int j = i; j < s.size(); j++)
            {
                if (i == j)
                    isPalindrome[i][j] = true;
                else if (i + 1 == j)
                    isPalindrome[i][j] = s[i] == s[j];
                else
                    isPalindrome[i][j] = (isPalindrome[i + 1][j - 1] && s[i] == s[j]);
            }
        }
    }

    vector<vector<string>> partition(string s)
    {
        result.clear();
        path.clear();
        computePalindrome(s);
        backTracking(s, 0);
        return result;
    }
};