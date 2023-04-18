/**
 * @file test.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <cstdio>
#include <limits.h>
using namespace std;

/**
 * @brief 使用右值引用传递值，方便函数调用啥参数都能传入
 * 
 * @tparam T 
 * @param value 
 */
template <class T>
void printbit(T &&value)
{
    cout << value << ":" << endl;
    char *p_e = (char *)&value;    // char是一个byte，char*类型转换取地址
    char *p = p_e + sizeof(T) - 1; // 类型总共的byte数目，从最后一个字节开始取
    for (; p >= p_e; p--)
    {
        for (int i = 7; i >= 0; i--) // 每个byte从最后一位bit开始输出
            cout << ((*p) & (1 << i) ? 1 : 0);
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    // 按照位输出int类型
    if(0)
    {
        int value = 10;
        printbit(value);
    }
    cout << "INT_MAX" << INT_MAX << endl;
    // 取反操作
    if(0)
    {
        int value = INT_MAX;
        printbit(1);
        printbit(~value);
        printbit(value);
        value = -value;
        printbit(value);
    }

    // 测试右值引用
    {
        int value = 10;
        int &valueleft = value;
        printbit(valueleft);

        int &&valueright = std::move(valueleft);
        printbit(valueright);

        int &&valueright1 = 1;
        printbit(valueright1);
    }

    return 0;
}