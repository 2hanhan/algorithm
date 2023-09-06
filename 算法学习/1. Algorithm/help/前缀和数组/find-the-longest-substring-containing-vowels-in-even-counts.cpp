/**
 * @file find-the-longest-substring-containing-vowels-in-even-counts.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-04
 * 1371. 每个元音包含偶数次的最长子字符串
 * https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findTheLongestSubstring(string s)
    {
        unordered_map<int, int> map; // 第次层出现的位置
        map[0] = -1;

        int max_length = 0;
        int count_aeiou = 0; // 16,8,4,2,1位置1代表奇数个，0代表偶数个
        for (int i = 0; i < s.size(); i++)
        {
            count_aeiou = count_aeiou ^ char_to_count(s[i]); // 当前的奇数偶数次数

            if (map.find(count_aeiou) != map.end())
            {
                max_length = max(max_length, i - map[count_aeiou]); // 奇偶数次数相等的，一减就都是偶数了
            }
            else
            {
                map[count_aeiou] = i;
            }
        }
        return max_length;
    }

    int char_to_count(char c)
    {
        if (c == 'a')
            return 1;
        else if (c == 'e')
            return 2;
        else if (c == 'i')
            return 4;
        else if (c == 'o')
            return 8;
        else if (c == 'u')
            return 16;
        else
            return 0;
    }
};