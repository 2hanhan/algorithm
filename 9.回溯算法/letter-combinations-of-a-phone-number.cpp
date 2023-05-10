/**
 * @file letter-combinations-of-a-phone-number.cpp
 * 17. 电话号码的字母组合
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <string>
using namespace std;
class Solution
{
public:
    const string letterMap[10] = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz", // 9
    };
    vector<string> result;
    string path;

    void backTracking(string digits, int index)
    {
        if (path.size() == digits.size())
        {
            result.push_back(path);
            return;
        }
        int digit = digits[index] - '0';
        string letters = letterMap[digit];
        for (int i = 0; i < letters.size(); i++)
        {
            path.push_back(letters[i]);
            backTracking(digits, index + 1);
            path.pop_back();
        }
    }
    vector<string> letterCombinations(string digits)
    {
        result.clear();
        path.clear();
        if (digits.empty())
            return result;
        backTracking(digits, 0);
        return result;
    }
};