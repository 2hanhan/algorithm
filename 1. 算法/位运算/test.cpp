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
#include<cstdio>
using namespace std;

int main(int argc, char **argv)
{
    // 按照位输出int类型
    {
        int value = 1;
        for (int i = 31; i >= 0; i--)
            cout<<(value & 1 << i);
    }

    return 0;
}