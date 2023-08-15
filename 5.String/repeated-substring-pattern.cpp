/**
 * @file repeated-substring-pattern.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 * 5.7 重复的子字符串
 * @copyright Copyright (c) 2022
 *
 */

#include <string>
#include <algorithm>
using namespace std;

// 移动匹配
// s+s里面去寻找s
class Solution0
{
public:
    bool repeatedSubstringPattern(string s)
    {
        // s+s掐头去尾
        string t = s + s;
        t.erase(t.begin());
        t.erase(t.end() - 1);

        // 掐头去尾的s+s中寻找s
        if (t.find(s) != std::string::npos)
            return true;
        return false;
    }
};

// 使用KMP不减一
class Solution1
{
public:
    void getNext(int *next, const string &s)
    {
        // 不减一的版本
        int j = 0;
        next[0] = 0;
        for (int i = 1; i < s.size(); i++)
        {
            while (j > 0 && s[i] != s[j])
            {
                j = next[j - 1];
            }
            if (s[i] == s[j])
            {
                j++;
            }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern(string s)
    {
        if (s.size() == 0)
        {
            return false;
        }

        // step 1 计算前缀表next数组
        int next[s.size()];
        getNext(next, s);

        // step 2 计算循环数组长度，判断是否循环
        // next 数组的最后一位的数值 等于 len-循环数值的长度
        //  循环数值的长度 = len - next[len - 1]
        int len = s.size();
        //  next数组最后一位不为0 并且 数组总长度%循环数组长度==0
        if (next[len - 1] != 0 && len % (len - next[len - 1]) == 0)
        {
            return true;
        }
        return false;
    }
};
