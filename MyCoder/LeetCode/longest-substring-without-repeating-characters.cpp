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
class Solution0
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

// 动态规划
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int size = s.size();
        if (size == 0)
            return 0;

        // base case
        int dp[size]; // 以i位置结尾的最长无重复子串
        dp[0] = 1;

        int result = 1;
        int pose[256]; // 上一次出现s[i]的位置
        memset(pose, -1, 256 * sizeof(int));
        pose[s[0]] = 0;
        for (int i = 1; i < size; i++)
        {
            if (pose[s[i]] < i - dp[i - 1]) // 上一个s[i]更靠前
                dp[i] = dp[i - 1] + 1;
            else
                dp[i] = i - pose[s[i]];
            pose[s[i]] = i;
            result = max(result, dp[i]);
        }

        return result;
    }
};

int main()
{
    string s = "abba";
    Solution soultion;
    cout << soultion.lengthOfLongestSubstring(s) << endl;
}