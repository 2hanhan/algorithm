/**
 * @file zuo-xuan-zhuan-zi-fu-chuan-lcof.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 * 6.5 左旋字符串
 * - 主要是解题思路
 * 首先翻转部分
 * 然后翻转整体
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string reverseLeftWords(string s, int n)
    {
        // step 1 翻转[0,n)
        reverse(s.begin(), s.begin() + n);
        // step 2 翻转[n,s.size())
        reverse(s.begin() + n, s.end());
        // step 3 翻转[0,s.size())
        reverse(s.begin(), s.end());
        return s;
    }
};