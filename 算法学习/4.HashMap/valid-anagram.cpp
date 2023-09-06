/**
 * @file valid-anagram.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-22
 * - 4.2 有效的字母异位词
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        // 统计26个字母出现次数
        int record[26] = {0};

        // 统计s中所以字母出现次数
        for (int i = 0; i < s.size(); i++)
        {
            record[s[i] - 'a']++;
        }
        // s中所以字母出现次数-t中所有字母出现次数
        for (int i = 0; i < t.size(); i++)
        {
            record[t[i] - 'a']--;
        }

        // 统计表不全为0返回false
        for (int i = 0; i < 26; i++)
        {
            if (record[i] != 0)
                return false;
        }

        // 统计表全部为0返回true
        return true;
    }
};