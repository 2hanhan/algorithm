/**
 * @file 24_06.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-20
 * 316. 去除重复字母
 * https://leetcode.cn/problems/remove-duplicate-letters/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 贪心算法
class Solution
{
public:
    string removeDuplicateLetters(string s)
    {
        vector<int> vis(26), num(26);
        for (char ch : s)
        {
            num[ch - 'a']++;
        }

        string stk;
        for (char ch : s)
        {
            if (!vis[ch - 'a'])
            {
                while (!stk.empty() && stk.back() > ch)
                {
                    if (num[stk.back() - 'a'] > 0)
                    {
                        vis[stk.back() - 'a'] = 0;
                        stk.pop_back();
                    }
                    else
                    {
                        break;
                    }
                }
                vis[ch - 'a'] = 1;
                stk.push_back(ch);
            }
            num[ch - 'a'] -= 1;
        }
        return stk;
    }
};