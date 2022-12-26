/**
 * @file ransom-note.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-22
 * - 4.7 赎金信
 * @copyright Copyright (c) 2022
 *
 */

#include <string>
#include <unordered_map>

using namespace std;

// 使用数组
class Solution
{
public:
    bool canConstruct(string ransomNote, string magazine)
    {
        if (ransomNote.size() > magazine.size())
            return false;

        int record[26] = {0};
        for (char s : magazine)
        {
            record[s - 'a']++;
        }

        // 计算是否够用
        for (char s : ransomNote)
        {
            record[s - 'a']--;
            if (record[s - 'a'] < 0)
                return false;
        }
        return true;
    }
};

// unordered_map
// class Solution
// {
// public:
//     bool canConstruct(string ransomNote, string magazine)
//     {
//         if (ransomNote.size() > magazine.size())
//             return false;

//         // 统计可用的
//         unordered_map<char, int> map;
//         for (char s : magazine)
//         {
//             map[s]++;
//         }

//         // 计算是否够用
//         for (char s : ransomNote)
//         {
//             map[s]--;
//             if (map[s] < 0)
//                 return false;
//         }
//         return true;
//     }
// };