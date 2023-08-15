/**
 * @file evaluate-reverse-polish-notation.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-28
 * https://leetcode.cn/problems/evaluate-reverse-polish-notation/
 * 逆波兰表达式求值 中等
 * 这个题目难度主要是题目的理解
 * 就是先放入两个操作数，
 * 完后放入运算符号，
 * 则对先前的两个操作数进行二元运算
 * 运算结果作为新的操作数放入
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
#include <string>
#include <stack>
using namespace std;

class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        stack<long long> st;
        for (int i = 0; i < tokens.size(); i++)
        {
            // 如果是运算符，取出2个数字并计算然后放入栈
            if (tokens[i] == "+" ||
                tokens[i] == "-" ||
                tokens[i] == "*" ||
                tokens[i] == "/")
            {
                // num1 + - * / num2
                // 栈取出的第一个数字是num2
                long long num2 = st.top();
                st.pop();
                long long num1 = st.top();
                st.pop();
                if (tokens[i] == "+")
                    st.push(num1 + num2);
                if (tokens[i] == "-")
                    st.push(num1 - num2);
                if (tokens[i] == "*")
                    st.push(num1 * num2);
                if (tokens[i] == "/")
                    st.push(num1 / num2);
            }
            // 如果不是运算符，直接放入数字
            else
            {
                st.push(stoll(tokens[i])); // 字符串转换为数字
            }
        }

        int result = st.top();
        st.pop();
        return result;
    }
};