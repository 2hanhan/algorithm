/**
 * @file ti-huan-kong-ge-lcof.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 * 5.3 替换空格
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <string>
using namespace std;

class Solution
{
public:
    string replaceSpace(string s)
    {
        // step 1 统计空格个数
        int count = 0;
        int oldi = s.size() - 1; // 原字符串最后一个元素
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
            {
                count++;
            }
        }
        // step 2 扩充数组
        s.resize(s.size() + count * 2);
        int newi = s.size() - 1; // 扩充后数组的最后一个元素
        // step 3 双指针从后往前替换元素
        while (oldi < newi)
        {
            if (s[oldi] == ' ')
            {
                s[newi] = '0';
                s[newi - 1] = '2';
                s[newi - 2] = '%';
                newi -= 3;
                oldi--;
            }
            else
            {
                s[newi] = s[oldi];
                newi--;
                oldi--;
            }
        }
        return s;
    }
};
