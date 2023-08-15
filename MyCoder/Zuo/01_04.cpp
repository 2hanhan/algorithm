/**
 * @file 01_04.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-14
 * 相邻字符的交换次数
一个数组中只有两种字符'G'和'B’，可以让所有的G都放在左侧，
所有的B都放在右侧, 或者可以让所有的G都放在右侧，所有的B都放在左侧,
但是只能在相邻字符之间进行交换操作，返回至少需要交换几次
 * @copyright Copyright (c) 2023
 *
 */
#include <bits/stdc++.h>
using namespace std;

//贪心
int solution(const string &s)
{
    int G_count = 0, B_count = 0;
    int G_result = 0, B_result = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'G')
        {
            G_result += i - G_count;
            G_count++;
        }
        else
        {
            B_result += i - B_count;
            B_count++;
        }
    }

    return min<int>(G_result, B_result);
}

int main()
{
    cout<<"输入字符串:"<<endl;
    string s;
    cin >> s;
    cout << "s:" << s << endl;

    cout << "最小交换次数:" << solution(s) << endl;
}