#include <bits/stdc++.h>

using namespace std;

// 修饰基本数据类型
void test01()
{
    const int a = 0;
    int const b = 0;
    // const int c;//! 报错
    // a = 10; //! 报错
    // int *c = &a; //! 报错
}

// 常量指针
void test02()
{
    int a = 0;
    int const b = 0;
    const int *c = &a;
    int const *d = &b;
    const int *e;
    e = &a;
    // *c = 10; //! 报错
    a = 10;
    // *d = 10; //! 报错
    int f = 1;
    c = &f;
    // int *g = &b; //! 报错
}

// 指针常量
void test03()
{
    int a = 0;
    int const b = 0;
    int *const c = &a;
    // int *const d; //! 报错
    // int *const e = &b;//! 报错
    int f = 0;
    *c = f;
    // c = &f;//! 报错
}

// 指针常量
void test04()
{
    int const a = 0;
    int b = 0;
    int const *const c = &a;
    const int *const d = &b;
}

void test05()
{
    int a = 0;
    const int b = 0;
    const int &c = a;
    const int &d = b;
    // const int &e; //! 报错
    // c = 10;//! 报错
}

class A
{
public:
    A(int _value_a) : value_a(_value_a)
    {
    }
    const int value_a;
    int value_b;
    void change_value_const(int &value_c) const
    {
        // value_b = 10;//! 报错
        value_c = value_b;
    }
    void change_value(int &value_c)
    {
        value_b = 10;
        value_c = value_b;
    }
};

// 修饰类对象
void test06()
{
    const A b(10);
    int d = 100;
    b.change_value_const(d);
    // b.change_value(d);//! 报错
}

int main()
{

    return 0;
}