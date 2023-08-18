/**
 * @file longest-substring-without-repeating-characters.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-16
 * 3. 无重复字符的最长子串
 * https://leetcode.cn/problems/longest-substring-without-repeating-characters/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 双指针
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_map<char, int> positon;
        int left = 0;
        int result = 0;

        for (int i = 0; i < s.size(); i++)
        {

            if (positon.find(s[i]) == positon.end() || positon[s[i]] < left)
            {
                positon[s[i]] = i;
            }
            else
            {
                result = max<int>(result, i - left);
                left = positon[s[i]] + 1;
                positon[s[i]] = i;
            }
        }
        return max<int>(result, s.size() - left);
    }
};

int main()
{
    string s = "abba";
    Solution soultion;
    cout << soultion.lengthOfLongestSubstring(s) << endl;
}