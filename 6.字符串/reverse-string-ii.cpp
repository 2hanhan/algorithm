/**
 * @file reverse-string-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 * 6.2 翻转字符串II
 * @copyright Copyright (c) 2022
 * - 这个题目的关键是理解化简题目的含义，如果题目直接使用下面的表述接方便理解了
 * - 本质上是翻转第 [2*k*i,2*k*i+k)处的字符串
 * reverse()函数翻转的是[a,b)迭代器直接的部分
 */

#include <algorithm>
#include <string>
using namespace std;

class Solution
{
public:
    string reverseStr(string s, int k)
    {
        for (int i = 0; i < s.size(); i += (2 * k))
        {
            if (i + k <= s.size())
            {
                reverse(s.begin() + i, s.begin() + i + k + 1);
            }
            else
            {
                reverse(s.begin() + 1, s.end());
            }
        }
        return s;
    }
};

class Solution
{
public:
    string reverseStr(string s, int k)
    {
        int pos = 0;
        int n = s.size();
        while (pos < n)
        {
            if (pos + k < n)
            {
                reverse(s.begin() + pos, s.begin() + pos + k);
            }
            else
            {
                reverse(s.begin() + pos, s.end());
            }
            pos += 2 * k;
        }
        return s;
    }
};