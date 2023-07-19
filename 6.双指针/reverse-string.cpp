/**
 * @file reverse-string.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 * 翻转字符串
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
using namespace std;

class Solution0
{
public:
    void reverseString(vector<char> &s)
    {
        //终止条件双指针相遇
        for (int i = 0, j = s.size() - 1; i < j; i++, j--)
        {
            swap(s[i], s[j]);
        }
    }
};

class Solution1
{
public:
    void reverseString(vector<char> &s)
    {
        //终止条件 从0开始的指针到达 size / 2
        for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--)
        {
            swap(s[i], s[j]);
        }
    }
};