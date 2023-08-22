/**
 * @file 09_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-19
 * 301. 删除无效的括号
 * https://leetcode.cn/problems/remove-invalid-parentheses/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<string> result;
    void process(int check_pose, int delete_pose, string s, char check_char, char delete_char)
    {
        // 删除check_char
        for (int count = 0, i = check_pose; i < s.size(); i++)
        {
            if (s[i] == check_char)
            {
                count++;
            }
            if (s[i] == delete_char)
            {
                count--;
            }

            if (count < 0)
            {
                for (int j = delete_pose; j <= i; j++)
                {
                    if (s[j] == delete_char && (j == delete_pose || s[j - 1] != delete_char))
                    {
                        string s1 = s.substr(0, j) + s.substr(j + 1, s.size() - j - 1); // 删除j位置
                        process(i, j, s1, check_char, delete_char);
                        // s1已经少了j位置的，j一定小于check和delete位置
                        // 所以位置i,j就相当于下一个位置，不会出现重复的删除和检查
                    }
                }
                return; // 该check位置已经使用过则返回
            }
        }

        // 到这里说明s中delete_char已经没有多余的了
        // 则需要删除多余的check_char，将数组s逆序
        // 同样的方法，删除check_char
        string s_re = s;
        reverse(s_re.begin(), s_re.end());
        if (check_char == '(')
        {
            // 第一次逆序check_char == '('
            process(0, 0, s_re, delete_char, check_char);
        }
        else
        {
            // 第二次逆序check_char == ')'，两个都已经匹配了
            // 返回逆序的结果即可
            result.push_back(s_re);
        }
    }

    vector<string> removeInvalidParentheses(string s)
    {
        result.clear();
        process(0, 0, s, '(', ')');
        return result;
    }
};

int main()
{
    Solution solution;
    string s = "(a)())()";
    solution.removeInvalidParentheses(s);
    return 0;
}