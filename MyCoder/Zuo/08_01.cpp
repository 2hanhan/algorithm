/**
 * @file 08_01.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-18
计算str表达式结果
给定一个字符串str，str表示一个公式，公式里可能有整数、加减乘除符号和左右 括号，返回公式的计算结果。
【举例】
```
str="48*((70-65)-43)+8*1"，返回-1816。
str="3+1*4"，返回7。
str="3+(1*4)"，返回7。
```
【说明】
1.可以认为给定的字符串一定是正确的公式，即不需要对str做公式有效性检查。  2.如果是负数，就需要用括号括起来，比如"4* (-3)"。但如果负数作为公式的开头 或括号部分的开头，则可以没有括号，比如"-3* 4"和"(-3* 4)"都是合法的。
3.不用考虑计算过程中会发生溢出的情况。
 * @copyright Copyright (c) 2023
 *
 */

// 递归
// 递归压入栈区

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    pair<int, int> func(string s, int i)
    {
        int result = 0;
        int cur = 0;
        queue<char> Q;

        while (i < s.size() && s[i] != ')') // 遇到数字
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                cur = cur * 10 + s[i] - '0';
            }
            else if (s[i] != ')') // 遇到运算符合
            {
                addNum(Q, cur);
                Q.push(s[i++]);
                cur = 0;
            }
            else
            {
                pair<int, int> temp = func(s, i + 1);
                cur = temp.first;
                i = temp.second + 1;
            }
        }
        addNum(Q, cur);
        return {getNum(que), i};
    }
    int result = 0;
    void addNum(queue<char> Q, int cur)
    {
    }
    int getNum(queue<char> Q)
    {
    }
};

int main()
{
    Solution solution;
    string s;
    solution.func(s, 0);
    return 0;
}