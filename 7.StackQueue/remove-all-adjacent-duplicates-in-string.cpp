/**
 * @file remove-all-adjacent-duplicates-in-string.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-28
 * https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/
 * 删除字符串中的所有相邻重复项
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class Solution0
{
public:
    string removeDuplicates(string s)
    {
        // 使用栈消除相同的元素
        stack<char> st;
        for (char x : s)
        {
            if (st.empty() || st.top() != x)
            {
                st.push(x);
            }
            else
            {
                st.pop();
            }
        }
        // 取出来放入string
        string result;
        while (!st.empty())
        {
            result.push_back(st.top());
            st.pop();
        }
        // 反转一下字符串
        reverse(result.begin(), result.end());
        return result;
    }
};

class Solution1
{
public:
    string removeDuplicates(string s)
    {
        string result;
        for (char x : s)
        {
            if (result.empty() || result.back() != x)
            {
                // 放入不同的元素
                result.push_back(x);
            }
            else
            {
                // 消除相同的元素
                result.pop_back();
            }
        }
        return result;
    }
};