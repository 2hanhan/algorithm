/**
 * @file find-the-index-of-the-first-occurrence-in-a-string.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 * 找出字符串中第一个匹配项的下标
 * @copyright Copyright (c) 2022
 * step 1 求前缀表
 */
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// 正常统计前缀表
class Solution0
{
public:
    void getNext(int *next, const string &s)
    {
        // 初始化
        int j = 0; // j代表相等的个数
        next[0] = 0;
        for (int i = 1; i < s.size(); i++) // i代表后缀
        {
            // 前后缀不同,则回退
            while (j > 0 && s[i] != s[j])
            {
                j = next[j - 1];
            }
            // 前后缀相同，相等的个数则+1
            if (s[i] == s[j])
            {
                j++;
            }
            // 更新当前的前缀表
            next[i] = j;
        }
    }
    int strStr(string haystack, string needle)
    {
        if (needle.size() == 0)
        {
            return 0;
        }

        int next[needle.size()];
        getNext(next, needle);

        int j = 0; // 统计以及相等的个数
        for (int i = 0; i < haystack.size(); i++)
        {
            while (j > 0 && haystack[i] != needle[j]) // 下一个不相等
            {
                j = next[j - 1]; // 使用前缀表进行回退
            }

            if (haystack[i] == needle[j]) // 下一个相等
            {
                j++; // 相等的个数+1
            }

            if (j == needle.size()) // 相等的个数达到要求
            {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};

// getNext()前缀表统计相同的个数-1
class Solution1
{
public:
    void getNext(int *next, const string &s)
    {
        int j = -1;
        next[0] = j;
        for (int i = 1; i < s.size(); i++)
        { // 注意i从1开始
            while (j >= 0 && s[i] != s[j + 1])
            {                // 前后缀不相同了
                j = next[j]; // 向前回退
            }
            if (s[i] == s[j + 1])
            { // 找到相同的前后缀
                j++;
            }
            next[i] = j; // 将j（前缀的长度）赋给next[i]
        }
    }
    int strStr(string haystack, string needle)
    {
        if (needle.size() == 0)
        {
            return 0;
        }
        int next[needle.size()];
        getNext(next, needle);
        int j = -1; // 因为next数组里记录的起始位置为-1
        for (int i = 0; i < haystack.size(); i++)
        { // 注意i就从0开始
            while (j >= 0 && haystack[i] != needle[j + 1])
            {                // 不匹配
                j = next[j]; // j 寻找之前匹配的位置
            }
            if (haystack[i] == needle[j + 1])
            {        // 匹配，j和i同时向后移动
                j++; // i的增加在for循环里
            }
            if (j == (needle.size() - 1))
            { // 文本串s里出现了模式串t
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};

int main(int argc, char **argv)
{
    string haystack = "";
    string needle = "aadaddaa";

    int next0[needle.size()];
    Solution0 solution0;
    solution0.getNext(next0, needle);

    int next1[needle.size()];
    Solution1 solution1;
    solution1.getNext(next1, needle);

    cout << "solution0:  solution:" << endl;
    for (int i = 0; i < needle.size(); i++)
    {
        cout << next0[i] << " " << next1[i] << endl;
    }
    cout << endl;

    return 0;
}
