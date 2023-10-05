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
        // 统计每个字符出现的次数
        for (char ch : s)
        {
            num[ch - 'a']++;
        }

        string stk; // 存储当前无重复的字符串
        for (char ch : s)
        {
            if (!vis[ch - 'a']) // 之后还有对应的字符
            {
                while (!stk.empty() && stk.back() > ch) // 栈顶部的字符字典序大于当前字符
                {
                    if (num[stk.back() - 'a'] > 0) // 之后栈顶字符还会出现，当前的元素清除掉，下次用到在添加回来
                    {
                        vis[stk.back() - 'a'] = 0;
                        stk.pop_back();
                    }
                    else // 之后栈顶字符不会再出现，只能保留此元素
                    {
                        break;
                    }
                }
                vis[ch - 'a'] = 1; // 已经统计过的字符
                stk.push_back(ch);
            }
            num[ch - 'a'] -= 1; // 计数减一
        }
        return stk;
    }
};