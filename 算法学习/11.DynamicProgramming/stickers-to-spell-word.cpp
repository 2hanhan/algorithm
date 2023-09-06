/**
 * @file stickers-to-spell-word.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-16
 * 691. 贴纸拼词
 * https://leetcode.cn/problems/stickers-to-spell-word/
 * @copyright Copyright (c) 2023
 *
 */
#include <bits/stdc++.h>
using namespace std;

// 暴力递归超时
class Solution0
{
public:
    int process(const vector<vector<int>> &stickers_map, vector<int> rest)
    {
        int first_char = -1;
        for (int i = 0; i < 26; i++)
        {
            if (rest[i] != 0)
            {
                first_char = i;
                break;
            }
        }
        if (first_char == -1)
            return 0;

        int min_num = INT_MAX;
        for (int j = 0; j < stickers_map.size(); j++)
        {
            // 没消除掉第一个
            if (stickers_map[j][first_char] == 0)
            {
                continue;
            }
            vector<int> rest1 = rest;
            for (int i = 0; i < 26; i++)
            {
                rest1[i] = stickers_map[j][i] > rest[i] ? 0 : rest[i] - stickers_map[j][i];
            }
            min_num = min<int>(min_num, process(stickers_map, rest1));
        }
        return min_num + (min_num == INT_MAX ? 0 : 1);
    }

    int minStickers(vector<string> &stickers, string target)
    {
        int n = stickers.size();
        vector<vector<int>> stickers_map(n, vector<int>(26, 0));
        for (int i = 0; i < n; i++)
        {
            for (char one_char : stickers[i])
            {
                stickers_map[i][one_char - 'a']++;
            }
        }

        vector<int> target_map(26, 0);
        for (char one_char : target)
        {
            target_map[one_char - 'a']++;
        }
        int result = process(stickers_map, target_map);
        return result == INT_MAX ? -1 : result;
    }
};

// 记忆化搜索 AC
class Solution1
{
public:
    unordered_map<string, int> dp;
    int process(const vector<vector<int>> &stickers_map, vector<int> rest)
    {
        string rest_s;
        int first_char = -1;
        for (int i = 0; i < 26; i++)
        {
            if (rest[i] != 0 && first_char == -1)
            {
                first_char = i;
            }
            for (int k = 0; k < rest[i]; k++)
            {
                char x = 'a' + i;
                rest_s.push_back(x);
            }
        }
        if (first_char == -1)
            return 0;

        if (dp.find(rest_s) != dp.end())
        {
            return dp[rest_s];
        }

        int min_num = INT_MAX;
        for (int j = 0; j < stickers_map.size(); j++)
        {
            // 没消除掉第一个
            if (stickers_map[j][first_char] == 0)
            {
                continue;
            }
            vector<int> rest1 = rest;
            for (int i = 0; i < 26; i++)
            {
                rest1[i] = stickers_map[j][i] > rest[i] ? 0 : rest[i] - stickers_map[j][i];
            }
            min_num = min<int>(min_num, process(stickers_map, rest1));
        }

        dp[rest_s] = min_num + (min_num == INT_MAX ? 0 : 1);
        return dp[rest_s];
    }

    int minStickers(vector<string> &stickers, string target)
    {
        int n = stickers.size();
        vector<vector<int>> stickers_map(n, vector<int>(26, 0));
        for (int i = 0; i < n; i++)
        {
            for (char one_char : stickers[i])
            {
                stickers_map[i][one_char - 'a']++;
            }
        }

        vector<int> target_map(26, 0);
        for (char one_char : target)
        {
            target_map[one_char - 'a']++;
        }
        int result = process(stickers_map, target_map);
        return result == INT_MAX ? -1 : result;
    }
};

// 官方题解
class Solution
{
public:
    int minStickers(vector<string> &stickers, string target)
    {
        int m = target.size();
        vector<int> dp(1 << m, -1);
        dp[0] = 0;
        function<int(int)> helper = [&](int mask)
        {
            if (dp[mask] != -1)
            {
                return dp[mask];
            }
            dp[mask] = m + 1;
            for (auto &sticker : stickers)
            {
                int left = mask;
                vector<int> cnt(26);
                for (char &c : sticker)
                {
                    cnt[c - 'a']++;
                }
                for (int i = 0; i < m; i++)
                {
                    if ((mask >> i & 1) && cnt[target[i] - 'a'] > 0)
                    {
                        cnt[target[i] - 'a']--;
                        left ^= 1 << i;
                    }
                }
                if (left < mask)
                {
                    dp[mask] = min(dp[mask], helper(left) + 1);
                }
            }
            return dp[mask];
        };
        int res = helper((1 << m) - 1);
        return res > m ? -1 : res;
    }
};

int main()
{
    Solution solution;

    vector<string> stickers;
    stickers.push_back("with");
    stickers.push_back("example");
    stickers.push_back("science");

    string target = "thehat";

    cout << solution.minStickers(stickers, target);

    return 0;
}
