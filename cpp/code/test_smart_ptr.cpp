#include <bits/stdc++.h>

using namespace std;

void test01()
{
    unique_ptr<string> p1(new string("test01"));
    unique_ptr<string> p2;
    // p2 = p1; //! 报错
}

int main()
{
    test01();
    return 0;
}