/**
 * @file word-break.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 139. 单词拆分
 * https://leetcode.cn/problems/word-break/
 * @copyright Copyright (c) 2023
 *
 */
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;
// class Solution
// {
// public:
//     bool wordBreak(string s, vector<string> &wordDict)
//     {
//         vector<bool> dp(s.size() + 1, false);
//         dp[0] = true;
//         int left = 0;

//         for (int i = 1; i <= s.size(); i++)
//         {
//             string world = string(s.begin() + left, s.begin() + i);
//             cout << i << ":" << world <<"  left:"<<left<<":"<<dp[left]<< endl;

//             for (int j = 0; j < wordDict.size(); j++)//! 只考虑了单词唯一拆分的情况
//             {
//                 if (dp[left] == true && world == wordDict[j])
//                 {
//                     left = i;
//                     dp[left] = true;
//                     break;
//                 }
//             }
//         }
//         return dp[s.size()];
//     }
// };

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++)
        { // 遍历背包
            for (int j = 0; j < i; j++)
            {                                     // 遍历物品
                string word = s.substr(j, i - j); // substr(起始位置，截取的个数)
                if (wordSet.find(word) != wordSet.end() && dp[j])
                {
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }
};

int main(int argc, char **argv)
{
    Solution solution;
    string s = "leetcode";
    vector<string> wordDict{"leet", "code"};
    bool result = solution.wordBreak(s, wordDict);
    cout << "result:" << result << endl;
    return 0;
}